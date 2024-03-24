#ifndef CONNECT6_AI_HUMANPLAYER_H
#define CONNECT6_AI_HUMANPLAYER_H


#include "Player.h"
#include "../Interface/Logger.h"

class HumanPlayer : public Player {
    Logger &logger;
public:
    HumanPlayer(Logger &logger);
    Move GetMove(const Board &board, const Move &prevMove) override;
};


#endif //CONNECT6_AI_HUMANPLAYER_H
