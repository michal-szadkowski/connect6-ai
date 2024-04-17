#ifndef CONNECT6_AI_RANDOMPLAYER_H
#define CONNECT6_AI_RANDOMPLAYER_H

#include <utility>
#include "Player.h"


/**
 * Player making random moves.
 */
class RandomPlayer : public Player
{
private:
    /**
     *
     * @param board Position to generate random move from.
     * @param prev Previously placed stone position.
     * @return Randomly generated empty position.
     */
    static StonePos GetRandomPos(const Board &board, StonePos prev);

public:
    RandomPlayer(const std::string &name, std::shared_ptr<InfoLogger> logger) : Player(name, std::move(logger)) {}


    /**
     * @return Random but legal move in current position.
     */
    Move GetMove(const Board &board, const Move &prevMove) override;
};

#endif // CONNECT6_AI_RANDOMPLAYER_H
