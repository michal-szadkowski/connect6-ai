#ifndef CONNECT6_AI_GAME_H
#define CONNECT6_AI_GAME_H


#include "../Interface/GameLogger.h"
#include "../Players/Player.h"
#include "Board.h"

class Game
{
private:
    Player &black;
    Player &white;
    Board board;

    std::shared_ptr<GameLogger> logger;

    std::vector<std::pair<Board, Move>> history;

        Move MakePlayerTurn(Player &player, const Move &prevMove);
        bool IsLegal(const Move &move);

        void MakeMove(const Move &move);

public:
        Game(Player &black, Player &white, std::shared_ptr<GameLogger> logger);

        Game(Player &black, Player &white, const Board &board, std::shared_ptr<GameLogger> logger);

        std::vector<std::pair<Board, Move>> GetHistory() { return history; }

        Color Play();
};


#endif // CONNECT6_AI_GAME_H
