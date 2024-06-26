#ifndef DQNTRAINENV_H
#define DQNTRAINENV_H
#include <memory>

#include "../../Dqn/Agent.h"
#include "../../Interface/GameLogger.h"
#include "../../Interface/InfoLogger.h"
#include "Environment.h"

struct PlayGamesResult
{
    int p1B = 0;
    int p1W = 0;
    int p2B = 0;
    int p2W = 0;
    int all = 0;
    double p1AccWin = 0;
    double p2AccWin = 0;
    double p1MvCnt = 0;
    double p2MvCnt = 0;

    PlayGamesResult() {}

    PlayGamesResult(std::pair<int, int> p1, std::pair<int, int> p2, int all, double p1AccWin, double p2AccWin, double p1MvCnt,
                    double p2MvCnt) : p1B(p1.first), p1W(p1.second), p2B(p2.first), p2W(p2.second), all(all), p1AccWin(p1AccWin),
                                      p2AccWin(p2AccWin), p1MvCnt(p1MvCnt), p2MvCnt(p2MvCnt) {}

    int P1() { return p1B + p1W; }
    int P2() { return p2B + p2W; }
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

    PlayGamesResult PlayGames(Agent& a1, Agent& a2, int gamesPerTh, int threads, bool remember, double eps);
    static void PrintResults(PlayGamesResult results);
    void PlayGameAndPrint(Agent& a1, Agent& a2, double eps);

public:
    DqnTrainEnv(std::shared_ptr<GameLogger> gameLogger, std::shared_ptr<InfoLogger> infoLogger, int agentMemory, int iterations, double eps,
                double epsDecay);

    void Run() override;

    void SetLoad(std::string loadPath);
    void SetCheckpointDir(std::string chPath);
    void SetSave(std::string outPath);
};


#endif // DQNTRAINENV_H
