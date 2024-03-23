#ifndef CONNECT6_AI_GAME_H
#define CONNECT6_AI_GAME_H


#include "Board.h"
#include "../Players/Player.h"

class Game {
private:
    Player &black;
    Player &white;
    Board board;

    Move MakePlayerTurn(Player &player, const Move &prevMove);
public:
    Game(Player &black, Player &white);
    Game(Player &black, Player &white, const Board &board);

    bool IsLegal(const Move &move);
    void MakeMove(const Move &move);

    Color Play();
    void PrintBoard();

};


#endif //CONNECT6_AI_GAME_H
