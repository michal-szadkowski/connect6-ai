#ifndef CONNECT6_AI_MCTSPLAYER_H
#define CONNECT6_AI_MCTSPLAYER_H


#include <memory>
#include "Player.h"
#include "../Mcts/Tree.h"
#include "../Interface/GameLogger.h"

class MctsPlayer : public Player
{
private:
    std::unique_ptr<Tree> tree;
    int expCount;
    int simCount;
    double expRate;

    static Color SimulateGame(const Board& board);
    void PostMoveToTree(const Move& move);
    void RunTreeAlgorithm();

public:
    MctsPlayer(const std::string& name, std::shared_ptr<InfoLogger> logger, int explorations = 250000, int simulations = 5,
               double expRate = 0.42);

    Move GetMove(const Board& board, const Move& prevMove) override;
};


#endif //CONNECT6_AI_MCTSPLAYER_H
