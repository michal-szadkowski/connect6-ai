#ifndef DQNTRAINENV_H
#define DQNTRAINENV_H
#include <memory>

#include "Environment.h"
#include "../../Dqn/Agent.h"
#include "../../Interface/GameLogger.h"
#include "../../Interface/InfoLogger.h"

class DqnTrainEnv final : public Environment
{
    std::shared_ptr<GameLogger> gameLogger{};
    std::shared_ptr<InfoLogger> infoLogger{};
    Agent agentCurrent;
    int iterations;

    double startEps, endEps;
    int epsDecIter;

    std::string load, checkpoint, save;

public:
    DqnTrainEnv(std::shared_ptr<GameLogger> gameLogger, std::shared_ptr<InfoLogger> infoLogger, int agentMemory, int iterations);
    void SetLoad(std::string loadPath);
    void SetCheckpointDir(std::string chPath);
    void SetSave(std::string outPath);
    void Eps(double start, double end, int iter);
    void Run() override;
    void LoadModel();
    std::pair<int, int> PlayGames(int gamesPerTh, int threads, double e, Agent& a1, Agent& a2);
    void PrintResults(const std::pair<int, int>& results, int total);
};


#endif //DQNTRAINENV_H
