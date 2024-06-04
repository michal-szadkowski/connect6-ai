#include "DqnTrainEnv.h"
#include <future>
#include <torch/torch.h>
#include <utility>
#include "../../Game/Game.h"
#include "../../Interface/NoLogger.h"
#include "../../Players/DqnPlayer.h"
#include "PlayEnv.h"

DqnTrainEnv::DqnTrainEnv(std::shared_ptr<GameLogger> gameLogger, std::shared_ptr<InfoLogger> infoLogger, int agentMemory, int iterations,
                         double eps, double epsDecay) :
    agentCurrent(agentMemory), gameLogger(gameLogger), infoLogger(infoLogger), iterations(iterations), eps(eps), epsDecay(epsDecay)
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
    for (int i = 0; i < iterations; ++i)
    {
        auto s = std::chrono::high_resolution_clock::now();

        const int games = 35;
        const int th = 10;
        std::cout << "it: " << i << " " << std::flush;

        auto results = PlayGames(games, th, eps, agentCurrent, agentCurrent);
        PrintResults(results);
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - s) << " e:" << eps
                  << "\t" << std::flush;
        s = std::chrono::high_resolution_clock::now();

        auto err = agentCurrent.Train(1000);
        std::cout << "  " << err << " " << std::flush;

        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - s) << "\t"
                  << std::flush;
        s = std::chrono::high_resolution_clock::now();

        const int evalGames = 10;
        auto eval = PlayGames(evalGames, th, 0.01, agentCurrent, agentPrev);
        PrintResults(eval);

        CheckPointModel(i);

        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - s);
        std::cout << " " << elapsed << "\t";


        if (eval.p1 >= (eval.all) * 0.55)
        {
            agentPrev = Agent(agentCurrent);
            sameAgentIters = 0;
            std::cout << "agent advances";
        }
        else if (eval.p1 <= (eval.all) * 0.4 || sameAgentIters > 50)
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

        eps *= epsDecay;

        std::cout << std::endl;

        if (i % 10 == 9)
            PlayGameAndPrint(agentCurrent, agentPrev, 0.01);
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


PlayGamesResult DqnTrainEnv::PlayGames(int gamesPerTh, int threads, double eps, Agent &a1, Agent &a2)
{
    torch::NoGradGuard noGrad;
    PlayGamesResult result;
    std::vector<std::future<PlayGamesResult>> paral;
    for (int i = 0; i < threads; i++)
    {
        auto gameLogger = std::make_shared<NoLogger>();

        paral.push_back(std::async(std::launch::async,
                                   [=]()
                                   {
                                       auto p1 = std::make_shared<DqnPlayer>("p1", a1, gameLogger, eps);
                                       auto p2 = std::make_shared<DqnPlayer>("p2", a2, gameLogger, eps);
                                       auto env = PlayEnv(p1, p2, gameLogger, gameLogger, gamesPerTh);
                                       auto res = env.PlayGames();
                                       return PlayGamesResult{res.first, res.second, gamesPerTh, p1->GetAccWin(), p2->GetAccWin()};
                                   }));
    }
    for (int i = 0; i < threads; i++)
    {
        auto r = paral[i].get();
        result.p1 += r.p1;
        result.p2 += r.p2;
        result.all += r.all;
        result.p1AccWin += r.p1AccWin;
        result.p2AccWin += r.p2AccWin;
    }
    result.p1AccWin /= result.all;
    result.p2AccWin /= result.all;
    return result;
}

void DqnTrainEnv::PrintResults(const PlayGamesResult results)
{
    std::cout << results.p1 << " / " << results.all - results.p1 - results.p2 << " / " << results.p2 << " ";
    std::cout << results.p1AccWin << " / " << results.p2AccWin << " " << std::flush;
}

void DqnTrainEnv::PlayGameAndPrint(Agent &a1, Agent &a2, double eps)
{
    auto gameLogger = std::make_shared<NoLogger>();
    auto p1 = std::make_shared<DqnPlayer>("p1", a1, gameLogger, eps);
    auto p2 = std::make_shared<DqnPlayer>("p2", a2, gameLogger, eps);

    auto game = Game(*p1, *p2, this->gameLogger);
    game.Play();
    std::cout << std::endl;
}
