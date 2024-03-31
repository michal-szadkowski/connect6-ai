#ifndef CONNECT6_AI_RANDOMPLAYER_H
#define CONNECT6_AI_RANDOMPLAYER_H

#include <functional>
#include <utility>
#include "Player.h"

class RandomPlayer : public Player {
private:
    static StonePos GetRandomPos(const Board &board, StonePos prev);
public:
    RandomPlayer(std::string name, std::shared_ptr<InfoLogger> logger) : Player(std::move(name), std::move(logger)) {}
    Move GetMove(const Board &board, const Move &prevMove) override;
};


#endif //CONNECT6_AI_RANDOMPLAYER_H
