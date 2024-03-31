#ifndef CONNECT6_AI_MCTSPLAYER_H
#define CONNECT6_AI_MCTSPLAYER_H


#include <memory>
#include "Player.h"
#include "../Mcts/Tree.h"
#include "../Interface/GameLogger.h"

class MctsPlayer : public Player {
private:
    std::unique_ptr<Tree> tree;
    int expCount = 250000;
    int simCount = 5;
    double expRate = 0.4;

    Color SimulateGame(const Board &board);
    void PostMoveToTree(const Move &move);
    void RunTreeAlgorithm();
public:
    MctsPlayer(std::shared_ptr<InfoLogger> logger, int explorations = 250000, int simulations = 5,
               double expRate = 0.4);

    Move GetMove(const Board &board, const Move &prevMove) override;
};


#endif //CONNECT6_AI_MCTSPLAYER_H
