#ifndef CONNECT6_AI_MCTSPLAYER_H
#define CONNECT6_AI_MCTSPLAYER_H


#include <memory>
#include "Player.h"
#include "../Mcts/Tree.h"

class MctsPlayer : public Player {
private:
    std::unique_ptr<Tree> tree;
    int timeLimitInMs;

    int allNodes = 0;

    template<typename T>
    static T SelectRandom(std::vector<T> vector);
    static int RandomInRange(int min, int max);

    Color SimulateGame(const Board &board);
public:
    MctsPlayer();
    Move GetMove(const Board &board, const Move &prevMove) override;

};


#endif //CONNECT6_AI_MCTSPLAYER_H
