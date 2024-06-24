#include "DqnTrainEnv.h"
#include <future>
#include <torch/torch.h>
#include <utility>
#include "../../Game/Game.h"
#include "../../Interface/NoLogger.h"
#include "../../Players/DqnPlayer.h"
#include "PlayEnv.h"

DqnTrainEnv::DqnTrainEnv(std::shared_ptr<GameLogger> gameLogger, std::shared_ptr<InfoLogger> infoLogger, int agentMemory, int iterations,
                         double eps, double epsDecay) : agentCurrent(agentMemory), gameLogger(gameLogger), infoLogger(infoLogger),
                                                        iterations(iterations), eps(eps), epsDecay(epsDecay)
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
    const int th = 10;
    LoadModel();
    Agent agentPrev(agentCurrent);
    int sameAgentIters = 0;
    for (int i = 0; i < iterations; ++i)
    {
        std::cout << "it: " << i << " " << std::flush;

        auto s = std::chrono::high_resolution_clock::now();
        const int games = 100;
        auto results = PlayGames(agentCurrent, agentCurrent, games, th, true, eps);
        PrintResults(results);
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - s) << " e:" << eps <<
            "\t" << std::flush;

        s = std::chrono::high_resolution_clock::now();
        auto err = agentCurrent.Train(30);
        std::cout << "  " << err << " " << std::flush;
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - s) << "\t" <<
            std::flush;
        s = std::chrono::high_resolution_clock::now();

        const int evalGames = 10;
        auto eval = PlayGames(agentCurrent, agentPrev, evalGames, th, true, 0.075);
        PrintResults(eval);

        CheckPointModel(i);

        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - s);
        std::cout << " " << elapsed << "\t";


        if (eval.P1() >= 55)
        {
            agentPrev = Agent(agentCurrent);
            sameAgentIters = 0;
            std::cout << "agent advances";
        }
        else if (eval.P1() <= 40 || sameAgentIters > 250)
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
            PlayGameAndPrint(agentCurrent, agentPrev, 0.075);
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
    if (i % 5 == 0 && !checkpoint.empty()) { agentCurrent.Save(checkpoint + std::format(+"ch{}.pt", i)); }
}

void DqnTrainEnv::SaveModel()
{
    if (!save.empty())
        agentCurrent.Save(save);
}


PlayGamesResult DqnTrainEnv::PlayGames(Agent& a1, Agent& a2, int gamesPerTh, int threads, bool remember, double eps)
{
    torch::NoGradGuard noGrad;
    PlayGamesResult result;
    std::vector<std::future<PlayGamesResult>> paral;
    for (int i = 0; i < threads; i++)
    {
        auto gameLogger = std::make_shared<NoLogger>();

        paral.push_back(std::async(std::launch::async, [=]()
        {
            auto p1 = std::make_shared<DqnPlayer>("p1", a1, gameLogger, eps, remember);
            auto p2 = std::make_shared<DqnPlayer>("p2", a2, gameLogger, eps, remember);
            auto env = PlayEnv(p1, p2, gameLogger, gameLogger, gamesPerTh);
            auto res = env.PlayGames();
            auto p1Wins = env.GetP1Wins();
            auto p2Wins = env.GetP2Wins();
            return PlayGamesResult{p1Wins, p2Wins, gamesPerTh, p1->GetAccWin(), p2->GetAccWin(), p1->GetMoveCnt(), p2->GetMoveCnt()};
        }));
    }
    for (int i = 0; i < threads; i++)
    {
        auto r = paral[i].get();
        result.p1B += r.p1B;
        result.p1W += r.p1W;
        result.p2B += r.p2B;
        result.p2W += r.p2W;
        result.all += r.all;
        result.p1AccWin += r.p1AccWin;
        result.p2AccWin += r.p2AccWin;
        result.p1MvCnt += r.p1MvCnt;
        result.p2MvCnt += r.p2MvCnt;
    }
    result.p1MvCnt /= result.all;
    result.p2MvCnt /= result.all;
    result.p1AccWin /= result.all;
    result.p2AccWin /= result.all;
    return result;
}

void DqnTrainEnv::PrintResults(const PlayGamesResult results)
{
    std::cout << "(" << results.p1B << " " << results.p1W << ") " << results.p1B + results.p1W << " / " << results.all - results.p1B -
        results.p1W - results.p2B - results.p2W << " / " << results.p2B + results.p2W << " (" << results.p2B << " " << results.p2W << ") ";

    std::cout << results.p1AccWin << " / " << results.p2AccWin << " " << results.p1MvCnt + results.p2MvCnt << " \t" << std::flush;
}

void DqnTrainEnv::PlayGameAndPrint(Agent& a1, Agent& a2, double eps)
{
    auto gameLogger = std::make_shared<NoLogger>();
    auto p1 = std::make_shared<DqnPlayer>("p1", a1, gameLogger, eps, false);
    auto p2 = std::make_shared<DqnPlayer>("p2", a2, gameLogger, eps, false);

    auto game = Game(*p1, *p2, this->gameLogger);
    game.Play();
    std::cout << std::endl;
}
