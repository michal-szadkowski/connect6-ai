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

public:
    PlayEnv(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2, std::shared_ptr<GameLogger> gameLogger,
            std::shared_ptr<InfoLogger> infoLogger, int gameCount = 1);

    void Run() override;
    std::pair<int, int> PlayGames() const;
};


#endif // PLAYENV_H
