#ifndef CONNECT6_AI_MCTSPLAYER_H
#define CONNECT6_AI_MCTSPLAYER_H


#include <memory>
#include "Player.h"
#include "../Mcts/Tree.h"

class MctsPlayer : public Player {
private:
    std::unique_ptr<Tree> tree;
    int expCount = 16000;
    int simCount = 1;

    int allNodes = 0;
    Color SimulateGame(const Board &board);
public:
    MctsPlayer();
    Move GetMove(const Board &board, const Move &prevMove) override;

    void PostMoveToTree(const Board &board, const Move &move);
};


#endif //CONNECT6_AI_MCTSPLAYER_H
