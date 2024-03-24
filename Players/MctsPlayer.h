#ifndef CONNECT6_AI_MCTSPLAYER_H
#define CONNECT6_AI_MCTSPLAYER_H


#include <memory>
#include "Player.h"
#include "../Mcts/Tree.h"
#include "../Interface/Logger.h"

class MctsPlayer : public Player {
private:
    std::unique_ptr<Tree> tree;
    int expCount = 250000;
    int simCount = 5;

    Color SimulateGame(const Board &board);
    void PostMoveToTree(const Move &move);
    void RunTreeAlgorithm();
    Logger &logger;
public:
    MctsPlayer(Logger &logger);
    Move GetMove(const Board &board, const Move &prevMove) override;
};


#endif //CONNECT6_AI_MCTSPLAYER_H
