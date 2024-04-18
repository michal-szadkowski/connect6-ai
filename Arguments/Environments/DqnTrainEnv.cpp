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

    for (int i = 0; i < iterations; ++i)
    {
        auto s = std::chrono::high_resolution_clock::now();

        const int games = 125;
        const int th = 10;
        std::cout << "it: " << i << " " << std::flush;

        auto results = PlayGames(games, th, true, agentCurrent, agentCurrent);
        PrintResults(results, games * th);
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - s) << std::flush;
        s = std::chrono::high_resolution_clock::now();

        auto err = agentCurrent.Train(2000);
        std::cout << "  " << err << " " << std::flush;

        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - s) << " "
                  << std::flush;
        s = std::chrono::high_resolution_clock::now();

        const int evalGames = 25;
        auto eval = PlayGames(evalGames, th, true, agentCurrent, agentPrev);
        PrintResults(eval, evalGames * th);
        if (eval.first > evalGames * th + 4)
            agentPrev = Agent(agentCurrent);
        else if (eval.first < evalGames * th - 4)
            agentCurrent = Agent(agentPrev);

        CheckPointModel(i);

        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - s);
        std::cout << " " << elapsed;
        std::cout << std::endl;
        if (i % 10 == 9)
            PlayGameAndPrint(agentCurrent, agentCurrent);
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


std::pair<int, int> DqnTrainEnv::PlayGames(int gamesPerTh, int threads, bool stochastic, Agent &a1, Agent &a2)
{
    torch::NoGradGuard noGrad;
    std::pair<int, int> result{0, 0};
    std::vector<std::future<std::pair<int, int>>> paral;
    for (int i = 0; i < threads; i++)
    {
        paral.push_back(std::async(std::launch::async,
                                   [&a1, &a2, stochastic, gamesPerTh]()
                                   {
                                       auto gameLogger = std::make_shared<NoLogger>();
                                       auto p1 = std::make_shared<DqnPlayer>("p1", a1, gameLogger, stochastic);
                                       auto p2 = std::make_shared<DqnPlayer>("p2", a2, gameLogger, stochastic);
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
    std::cout << results.first << " / " << total - results.first - results.second << " / " << results.second << "\t" << std::flush;
}

void DqnTrainEnv::PlayGameAndPrint(Agent &a1, Agent &a2)
{
    auto gameLogger = std::make_shared<NoLogger>();
    auto p1 = std::make_shared<DqnPlayer>("p1", a1, gameLogger, true);
    auto p2 = std::make_shared<DqnPlayer>("p2", a2, gameLogger, true);

    auto game = Game(*p1, *p2, this->gameLogger);
    game.Play();
    std::cout << std::endl;
}
