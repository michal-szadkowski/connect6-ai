#include "DqnTrainEnv.h"
#include <torch/torch.h>
#include <utility>
#include <future>

#include "PlayEnv.h"
#include "../../Game/Game.h"
#include "../../Interface/NoLogger.h"
#include "../../Players/DqnPlayer.h"

DqnTrainEnv::DqnTrainEnv(std::shared_ptr<GameLogger> gameLogger, std::shared_ptr<InfoLogger> infoLogger, int agentMemory, int iterations):
    agentCurrent(agentMemory), gameLogger(std::move(std::move(gameLogger))), infoLogger(std::move(infoLogger)), iterations(iterations)
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

void DqnTrainEnv::Eps(double start, double end, int iter)
{
    startEps = start;
    endEps = end;
    epsDecIter = iter;
}

void DqnTrainEnv::Run()
{
    LoadModel();
    for (int i = 0; i < iterations; ++i)
    {
        Agent agentPrev(agentCurrent);
        auto s = std::chrono::high_resolution_clock::now();

        double e = std::max(startEps - i * (startEps - endEps) / epsDecIter, endEps);

        const int games = 150;
        const int th = 12;
        auto results = PlayGames(games, th, e, agentCurrent, agentCurrent);
        PrintResults(results, games * th);

        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - s) << std::flush;
        s = std::chrono::high_resolution_clock::now();

        auto err = agentCurrent.Train(500);
        std::cout << "  " << err << " " << std::flush;

        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - s) << std::flush;
        s = std::chrono::high_resolution_clock::now();


        auto eval = PlayGames(40, th, 0, agentCurrent, agentPrev);
        PrintResults(eval, 40 * th);

        // if (i % 500 == 0) { agentCurrent.Save(checkpoint + std::format(+"ch{}.pt", i)); }


        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - s);

        std::cout << std::format(" {} {}", err, elapsed.count());
        std::cout << std::endl;
    }
}

void DqnTrainEnv::LoadModel()
{
    if (!load.empty())
        agentCurrent.Load(load);
}


std::pair<int, int> DqnTrainEnv::PlayGames(int gamesPerTh, int threads, double e, Agent& a1, Agent& a2)
{
    std::pair<int, int> result{0, 0};
    std::vector<std::future<std::pair<int, int>>> paral;
    for (int i = 0; i < threads; i++)
    {
        paral.push_back(std::async(std::launch::async, [&a1,&a2,e,gamesPerTh]()
        {
            auto gameLogger = std::make_shared<NoLogger>();

            auto p1 = std::make_shared<DqnPlayer>("p1", a1, std::make_shared<NoLogger>(), e);
            auto p2 = std::make_shared<DqnPlayer>("p2", a2, std::make_shared<NoLogger>(), e);
            auto env = PlayEnv(p1, p2, std::make_shared<NoLogger>(), std::make_shared<NoLogger>(), gamesPerTh);

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

void DqnTrainEnv::PrintResults(const std::pair<int, int>& results, const int total)
{
    std::cout << results.first << " / " << total - results.first - results.second << " / " << results.second << "\t" << std::flush;
}
