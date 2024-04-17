#ifndef CONNECT6_AI_HUMANPLAYER_H
#define CONNECT6_AI_HUMANPLAYER_H


#include "../Interface/GameLogger.h"
#include "../Interface/InfoLogger.h"
#include "Player.h"


/**
 * Player class in which the user chooses the move.
 */
class HumanPlayer : public Player
{
public:
    HumanPlayer(const std::string &name, std::shared_ptr<InfoLogger> logger);
    /**
     * Waits for user input from cin.
     * @return Move made by user.
     */
    Move GetMove(const Board &board, const Move &prevMove) override;
};


#endif // CONNECT6_AI_HUMANPLAYER_H
