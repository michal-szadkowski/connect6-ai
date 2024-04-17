#ifndef CONNECT6_AI_TREE_H
#define CONNECT6_AI_TREE_H

#include <memory>
#include "Node.h"

/**
 * Class encapsulates game tree built by mcts algorithm.
 */
class Tree
{
private:
    Board rootBoard;
    std::shared_ptr<Node> root;


    /**
     * @return Node from root which corresponds to making move at position with color
     */
    std::shared_ptr<Node> GetNodeCorrespondingToPos(const StonePos &pos, const Color &col) const;

    /**
     * @return Most visited node from vector.
     */
    static std::shared_ptr<Node> GetBestFrom(std::vector<std::shared_ptr<Node>> vector);


    /**
     * Filters input vector to leave only unexplored nodes.
     * @return New vector containing only unexplored nodes from input one.
     */
    static std::vector<std::shared_ptr<Node>> FindUnexplored(const std::vector<std::shared_ptr<Node>> &all);

public:
    /**
     * Creates tree with empty board as root position.
     */
    Tree();

    /**
     * Creates tree with given board as root position.
     */
    explicit Tree(const Board &board);


    /**
     * Cuts branches from root which do not correspond to given position and then moves root to only remaining children node.
     */
    void PushMoveToTree(const StonePos &pos, const Color &col);

    /**
     * @return Current root of the tree.
     */
    std::shared_ptr<Node> GetRoot() { return root; }


    /**
     * @return Two most visited nodes such that second is a child of the first.
     */
    std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> GetBestSequence();


    /**
     * Selects a leaf going down from root based on UCT formula.
     * @param expRate Exploration rate.
     * @return Selected leaf
     */
    std::shared_ptr<Node> SelectLeaf(double expRate) const;

    /**
     * If input node has no children it creates them and then selects random unexplored children.
     * @param node Node which is fully or partially unexplored.
     */
    std::shared_ptr<Node> ExpandAndGetForSimulation(const std::shared_ptr<Node> &node);


    /**
     * Calculates position for given node.
     */
    Board GetBoardForNode(const std::shared_ptr<Node> &node) const;
};


#endif // CONNECT6_AI_TREE_H
