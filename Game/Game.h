#ifndef CONNECT6_AI_GAME_H
#define CONNECT6_AI_GAME_H


#include "Board.h"
#include "../Players/Player.h"

class Game {
private:
    Player &black;
    Player &white;
    Color turn = Color::Black;
    Board board;

public:
    Game(Player &black, Player &white);

    std::vector<Move> GetMoves();
    bool IsLegal(const Move &move);
    bool MakeMove(const Move &move);

    Color CheckForEndAfter(Move move);

    Color Play();
    void PrintBoard();

};


#endif //CONNECT6_AI_GAME_H
