#ifndef CONNECT6_AI_MCTSPLAYER_H
#define CONNECT6_AI_MCTSPLAYER_H

#include <memory>
#include "../Mcts/Tree.h"
#include "Player.h"

/**
 * Player class implementing monte carlo tree search algorithm.
 */
class MctsPlayer : public Player
{
private:
    std::unique_ptr<Tree> tree;
    int expCount;
    int simCount;
    double expRate;

    /**
     * Simulates game using random player. Used in MCTS to provide evaluation of
     * the position.
     * @param board Position to run simulation from.
     * @return Winner of simulated game.
     */
    static Color SimulateGame(const Board &board);
    /**
     * Updates internal game tree based on move.
     * @param move Move to update tree on.
     */
    void PostMoveToTree(const Move &move);
    /**
     * Runs cycle Selection->Expansion->Simulation->Propagation expCount number of
     * times.
     */
    void RunTreeAlgorithm();

public:
    /**
     * @param explorations Number of times a mcts cycle is performed.
     * @param simulations Game simulation to perform in each cycle.
     * @param expRate Exploration rate in selection phase. The bigger the wider
     * the exploration.
     */
    MctsPlayer(const std::string &name, std::shared_ptr<InfoLogger> logger, int explorations = 250000, int simulations = 5,
               double expRate = 0.42);

    /**
     * Overrided from Player class. Implements MCTS algorithm.
     * @return Move based on MCTS algorithm.
     */
    Move GetMove(const Board &board, const Move &prevMove) override;
};

#endif // CONNECT6_AI_MCTSPLAYER_H
