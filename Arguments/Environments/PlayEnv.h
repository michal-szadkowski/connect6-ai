#ifndef PLAYENV_H
#define PLAYENV_H
#include "Environment.h"
#include "../../Interface/GameLogger.h"
#include "../../Players/Player.h"

/**
 * Environment facilitating playing game with two players
 */
class PlayEnv final : public Environment
{
private:
    std::shared_ptr<Player> p1;
    std::shared_ptr<Player> p2;
    int gameCount = 1;
    std::shared_ptr<GameLogger> gameLogger;
    std::shared_ptr<InfoLogger> infoLogger;

public:
    /**
     * Creates playing environment with two players playing specified amount of games
     * @param p1 First player
     * @param p2 Second player
     * @param gameCount Amount of games
     */
    PlayEnv(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2, std::shared_ptr<GameLogger> gameLogger,
            std::shared_ptr<InfoLogger> infoLogger, int gameCount = 1);

    /**
     * Runs the environment
     */
    void Run() override;

    /**
     * Plays gameCount games switching players after each game
     * @return Amount of wins by first and second player
     */
    std::pair<int, int> PlayGames() const;
};


#endif //PLAYENV_H
