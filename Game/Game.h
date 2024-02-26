#ifndef CONNECT6_AI_GAME_H
#define CONNECT6_AI_GAME_H


#include "Board.h"
#include "../Players/Player.h"

class Game {
    Board board;
    Player &black;
    Player &white;
public:
    Game(Player &black, Player &white);
    Color Play();

};


#endif //CONNECT6_AI_GAME_H
