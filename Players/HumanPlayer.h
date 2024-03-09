#ifndef CONNECT6_AI_HUMANPLAYER_H
#define CONNECT6_AI_HUMANPLAYER_H


#include "Player.h"

class HumanPlayer : public Player {
public:
    Move GetMove(const Board &board, const Move &prevMove) override;
};


#endif //CONNECT6_AI_HUMANPLAYER_H
