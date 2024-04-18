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
private:
    /**
     * Request position from user until it is valid.
     * @param board Board to request move in
     * @param prev Previously placed stone by user, in order to check if new input is different (not placing two stones in same spot)
     */
    StonePos RequestMove(const Board &board, const StonePos &prev);

public:
    HumanPlayer(const std::string &name, std::shared_ptr<InfoLogger> logger);
    /**
     * Waits for user input from cin.
     * @return Move made by user.
     */
    Move GetMove(const Board &board, const Move &prevMove) override;
};


#endif // CONNECT6_AI_HUMANPLAYER_H
