#ifndef CONNECT6_AI_PLAYER_H
#define CONNECT6_AI_PLAYER_H

#include <memory>
#include "../Game/Board.h"
#include "../Game/Move.h"
#include "../Interface/InfoLogger.h"

/**
 * Absract class providing interface for player in game environment. Provides
 * functions to set and get color and get name.
 */
class Player
{
private:
    std::string name;
    Color color = Color::None;

protected:
    std::shared_ptr<InfoLogger> logger;

public:
    /**
     * @param name Name of player, set in environment based on parameters.
     * @param logger Logger for logging additional info during game.
     */
    Player(std::string name, std::shared_ptr<InfoLogger> logger);
    /**
     * @return Name of player
     */
    std::string Name();

    /**
     * @param newColor Sets color of player, used for playing multiple games in a
     * row to switch players.
     */
    void SetColor(Color newColor);
    /**
     * @return Current color of player.
     */
    Color GetColor();

    /**
     * Abstract function overrided by players. Used to decide which move to make.
     * @param board Current position.
     * @param prevMove Previous move made by opponent. Can be used to update
     * internal state of a player.
     * @return Move decided by player.
     */
    virtual Move GetMove(const Board &board, const Move &prevMove) = 0;
    virtual ~Player() = default;
};

#endif // CONNECT6_AI_PLAYER_H
