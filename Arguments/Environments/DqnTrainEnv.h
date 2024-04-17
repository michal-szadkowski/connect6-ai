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

    std::string load, checkpoint, save;

public:
    DqnTrainEnv(std::shared_ptr<GameLogger> gameLogger, std::shared_ptr<InfoLogger> infoLogger, int agentMemory, int iterations);
    void SetLoad(std::string loadPath);
    void SetCheckpointDir(std::string chPath);
    void SetSave(std::string outPath);
    void Eps(double start, double end, int iter);
    void Run() override;
    void LoadModel();
    void CheckPointModel(int i);
    void SaveModel();
    std::pair<int, int> PlayGames(int gamesPerTh, int threads, bool stochastic, Agent& a1, Agent& a2);
    void PrintResults(const std::pair<int, int>& results, int total);
    void PlayGameAndPrint(Agent& a1, Agent& a2);
};


#endif //DQNTRAINENV_H
