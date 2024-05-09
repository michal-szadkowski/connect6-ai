#ifndef CONNECT6_AI_HUMANPLAYER_H
#define CONNECT6_AI_HUMANPLAYER_H


#include "../Interface/GameLogger.h"
#include "../Interface/InfoLogger.h"
#include "Player.h"


class HumanPlayer : public Player
{
private:
        StonePos RequestMove(const Board &board, const StonePos &prev);

public:
    HumanPlayer(const std::string &name, std::shared_ptr<InfoLogger> logger);
        Move GetMove(const Board &board, const Move &prevMove) override;
};


#endif // CONNECT6_AI_HUMANPLAYER_H
