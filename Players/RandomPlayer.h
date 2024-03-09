#ifndef CONNECT6_AI_RANDOMPLAYER_H
#define CONNECT6_AI_RANDOMPLAYER_H

#include <functional>
#include "Player.h"

class RandomPlayer : public Player {
private:
    std::function<int(void)> rng;
    StonePos GetRandomPos(const Board &board, StonePos prev);
public:
    RandomPlayer();
    Move GetMove(const Board &board, const Move &prevMove) override;

};


#endif //CONNECT6_AI_RANDOMPLAYER_H
