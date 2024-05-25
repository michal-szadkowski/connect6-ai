#include "DqnTrainEnv.h"
#include <future>
#include <torch/torch.h>
#include <utility>
#include "../../Game/Game.h"
#include "../../Interface/NoLogger.h"
#include "../../Players/DqnPlayer.h"
#include "PlayEnv.h"

DqnTrainEnv::DqnTrainEnv(std::shared_ptr<GameLogger> gameLogger, std::shared_ptr<InfoLogger> infoLogger, int agentMemory, int iterations) :
    agentCurrent(agentMemory), gameLogger(gameLogger), infoLogger(infoLogger), iterations(iterations)
{
    if (torch::cuda::is_available())
    {
        std::cout << "CUDA is available! Training on GPU." << std::endl;
        agentCurrent.ToDevice(torch::Device(torch::kCUDA));
    }
}

void DqnTrainEnv::SetLoad(std::string loadPath) { load = std::move(loadPath); }
void DqnTrainEnv::SetCheckpointDir(std::string chPath) { checkpoint = std::move(chPath); }
void DqnTrainEnv::SetSave(std::string outPath) { save = std::move(outPath); }


void DqnTrainEnv::Run()
{
    LoadModel();
    Agent agentPrev(agentCurrent);
    int sameAgentIters = 0;
    double eps = 0.4;
    for (int i = 0; i < iterations; ++i)
    {
        auto s = std::chrono::high_resolution_clock::now();

        const int games = 70;
        const int th = 10;
        std::cout << "it: " << i << " " << std::flush;

        auto results = PlayGames(games, th, eps, agentCurrent, agentCurrent);
        PrintResults(results, games * th);
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - s) << " e:" << eps
                  << "\t" << std::flush;
        s = std::chrono::high_resolution_clock::now();

        auto err = agentCurrent.Train(1500);
        std::cout << "  " << err << " " << std::flush;

        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - s) << "\t"
                  << std::flush;
        s = std::chrono::high_resolution_clock::now();

        const int evalGames = 10;
        auto eval = PlayGames(evalGames, th, eps / 3, agentCurrent, agentPrev);
        PrintResults(eval, evalGames * th);

        CheckPointModel(i);

        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - s);
        std::cout << " " << elapsed << "\t";


        if (eval.first >= (evalGames * th) * 0.55)
        {
            agentPrev = Agent(agentCurrent);
            sameAgentIters = 0;
            std::cout << "agent advances";
        }
        else if (eval.first <= (evalGames * th) * 0.4 || sameAgentIters > 50)
        {
            agentCurrent = Agent(agentPrev);
            sameAgentIters = 0;
            std::cout << "agent discarded";
        }
        else
        {
            sameAgentIters++;
            std::cout << "agent age: " << sameAgentIters;
        }

        // if (i % 3 == 0)
        eps *= 0.99;

        std::cout << std::endl;

        if (i % 10 == 9)
            PlayGameAndPrint(agentCurrent, agentPrev);
    }
    SaveModel();
}

void DqnTrainEnv::LoadModel()
{
    if (!load.empty())
        agentCurrent.Load(load);
}

void DqnTrainEnv::CheckPointModel(int i)
{
    if (i % 5 == 0 && !checkpoint.empty())
    {
        agentCurrent.Save(checkpoint + std::format(+"ch{}.pt", i));
    }
}

void DqnTrainEnv::SaveModel()
{
    if (!save.empty())
        agentCurrent.Save(save);
}


std::pair<int, int> DqnTrainEnv::PlayGames(int gamesPerTh, int threads, double eps, Agent &a1, Agent &a2)
{
    torch::NoGradGuard noGrad;
    std::pair<int, int> result{0, 0};
    std::vector<std::future<std::pair<int, int>>> paral;
    for (int i = 0; i < threads; i++)
    {
        auto gameLogger = std::make_shared<NoLogger>();
        auto p1 = std::make_shared<DqnPlayer>("p1", a1, gameLogger, eps);
        auto p2 = std::make_shared<DqnPlayer>("p2", a2, gameLogger, eps);
        paral.push_back(std::async(std::launch::async,
                                   [=]()
                                   {
                                       auto env = PlayEnv(p1, p2, gameLogger, gameLogger, gamesPerTh);
                                       return env.PlayGames();
                                   }));
    }
    for (int i = 0; i < threads; i++)
    {
        auto r = paral[i].get();
        result.first += r.first;
        result.second += r.second;
    }
    return result;
}

void DqnTrainEnv::PrintResults(const std::pair<int, int> &results, const int total)
{
    std::cout << results.first << " / " << total - results.first - results.second << " / " << results.second << " " << std::flush;
}

void DqnTrainEnv::PlayGameAndPrint(Agent &a1, Agent &a2)
{
    auto gameLogger = std::make_shared<NoLogger>();
    auto p1 = std::make_shared<DqnPlayer>("p1", a1, gameLogger, 0.1);
    auto p2 = std::make_shared<DqnPlayer>("p2", a2, gameLogger, 0.1);

    auto game = Game(*p1, *p2, this->gameLogger);
    game.Play();
    std::cout << std::endl;
}
