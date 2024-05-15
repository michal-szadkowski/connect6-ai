#ifndef DQNTRAINENV_H
#define DQNTRAINENV_H
#include <memory>

#include "../../Dqn/Agent.h"
#include "../../Interface/GameLogger.h"
#include "../../Interface/InfoLogger.h"
#include "Environment.h"

class DqnTrainEnv final : public Environment
{
    std::shared_ptr<GameLogger> gameLogger{};
    std::shared_ptr<InfoLogger> infoLogger{};
    Agent agentCurrent;
    int iterations;

    std::string load, checkpoint, save;

    void LoadModel();
    void CheckPointModel(int i);

    void SaveModel();
    std::pair<int, int> PlayGames(int gamesPerTh, int threads, double eps, Agent &a1, Agent &a2);
    void PrintResults(const std::pair<int, int> &results, int total);
    void PlayGameAndPrint(Agent &a1, Agent &a2);

public:
    DqnTrainEnv(std::shared_ptr<GameLogger> gameLogger, std::shared_ptr<InfoLogger> infoLogger, int agentMemory, int iterations);

    void Run() override;

    void SetLoad(std::string loadPath);
    void SetCheckpointDir(std::string chPath);
    void SetSave(std::string outPath);
};


#endif // DQNTRAINENV_H
