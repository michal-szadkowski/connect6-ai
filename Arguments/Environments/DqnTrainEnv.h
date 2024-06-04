#ifndef DQNTRAINENV_H
#define DQNTRAINENV_H
#include <memory>

#include "../../Dqn/Agent.h"
#include "../../Interface/GameLogger.h"
#include "../../Interface/InfoLogger.h"
#include "Environment.h"

struct PlayGamesResult
{
    int p1 = 0;
    int p2 = 0;
    int all = 0;
    double p1AccWin = 0;
    double p2AccWin = 0;
};


class DqnTrainEnv final : public Environment
{
    std::shared_ptr<GameLogger> gameLogger{};
    std::shared_ptr<InfoLogger> infoLogger{};

    Agent agentCurrent;
    int iterations;

    double eps;
    double epsDecay;

    std::string load, checkpoint, save;

    void LoadModel();
    void CheckPointModel(int i);

    void SaveModel();
    PlayGamesResult PlayGames(int gamesPerTh, int threads, double eps, Agent &a1, Agent &a2);
    static void PrintResults(PlayGamesResult results);
    void PlayGameAndPrint(Agent &a1, Agent &a2, double eps);

public:
    DqnTrainEnv(std::shared_ptr<GameLogger> gameLogger, std::shared_ptr<InfoLogger> infoLogger, int agentMemory, int iterations, double eps,
                double epsDecay);

    void Run() override;

    void SetLoad(std::string loadPath);
    void SetCheckpointDir(std::string chPath);
    void SetSave(std::string outPath);
};


#endif // DQNTRAINENV_H
