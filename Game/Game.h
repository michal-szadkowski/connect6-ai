#ifndef CONNECT6_AI_GAME_H
#define CONNECT6_AI_GAME_H


#include "../Interface/GameLogger.h"
#include "../Players/Player.h"
#include "Board.h"

/**
 * Represents game of connect6
 */
class Game
{
private:
    Player &black;
    Player &white;
    Board board;

    std::shared_ptr<GameLogger> logger;

    std::vector<std::pair<Board, Move>> history;

    /**
     * Queries player for move
     * @param player Player to request move from
     * @param prevMove Previous move made by opponent of player
     * @return Move decided by player
     */
    Move MakePlayerTurn(Player &player, const Move &prevMove);
    /**
     * Checks if the move is legal in current position
     */
    bool IsLegal(const Move &move);

    /**
     * Makes move on the board
     */
    void MakeMove(const Move &move);

public:
    /**
     * Creates game with two players in default position
     */
    Game(Player &black, Player &white, std::shared_ptr<GameLogger> logger);

    /**
     * Creates game with two players from given position
     */
    Game(Player &black, Player &white, const Board &board, std::shared_ptr<GameLogger> logger);

    /**
     * @return History of moves made during the game
     */
    std::vector<std::pair<Board, Move>> GetHistory() { return history; }

    /**
     * Queries both players for moves and makes them on the board until there is no result
     * @return Winner of the game
     */
    Color Play();
};


#endif // CONNECT6_AI_GAME_H
