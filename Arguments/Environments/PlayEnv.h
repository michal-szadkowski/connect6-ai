#ifndef PLAYENV_H
#define PLAYENV_H
#include "../../Interface/GameLogger.h"
#include "../../Players/Player.h"
#include "Environment.h"


class PlayEnv final : public Environment
{
private:
    std::shared_ptr<Player> p1;
    std::shared_ptr<Player> p2;
    int gameCount = 1;
    std::shared_ptr<GameLogger> gameLogger;
    std::shared_ptr<InfoLogger> infoLogger;
    int p1WhiteWins = 0;
    int p1BlackWins = 0;
    int p2WhiteWins = 0;
    int p2BlackWins = 0;

public:
    PlayEnv(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2, std::shared_ptr<GameLogger> gameLogger,
            std::shared_ptr<InfoLogger> infoLogger, int gameCount = 1);

    void Run() override;
    std::pair<int, int> PlayGames();
    std::pair<int, int> GetP1Wins() { return {p1BlackWins, p1WhiteWins}; }
    std::pair<int, int> GetP2Wins() { return {p2BlackWins, p2WhiteWins}; }
};


#endif // PLAYENV_H
