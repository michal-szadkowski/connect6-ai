#ifndef CONNECT6_AI_HUMANPLAYER_H
#define CONNECT6_AI_HUMANPLAYER_H


#include "Player.h"

class HumanPlayer : public Player {
public:
    Move GetMove(Board &board) override;
};


#endif //CONNECT6_AI_HUMANPLAYER_H
