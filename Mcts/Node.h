#ifndef CONNECT6_AI_NODE_H
#define CONNECT6_AI_NODE_H

#include <memory>
#include <vector>
#include "../Game/Board.h"
#include "../Game/Color.h"
#include "../Game/StonePos.h"


/**
 * Represents single stone placed on a board
 */
class Node : public std::enable_shared_from_this<Node>
{
private:
    std::vector<std::shared_ptr<Node>> children;
    std::weak_ptr<Node> parent;

    bool expanded = false;
    StonePos pos;
    Color color;

    bool isFirstOfMove;

    unsigned int visitCount = 0;
    int score = 0;

public:
    /**
     * @param parent Parent node of new node
     * @param pos Sone placed node represents
     * @param color Color of placed stone
     * @param isFirst Wheather node is first stone of move or second
     */
    Node(std::weak_ptr<Node> parent, StonePos pos, Color color, bool isFirst);

    /**
     * @return Position of the node
     */
    StonePos GetPosition() const { return pos; }

    /**
     * @return Color of the node
     */
    Color GetColor() const { return color; }

    /**
     * Calculates the UCT value based on current score, visit count and parent visit count
     * @param expRate Exploration rate
     */
    double GetValue(double expRate) const;


    /**
     * @return Number of times this node has been visited
     */
    unsigned int GetVisitCount() const;


    /**
     * @return Wheather this node is fully explored
     */
    bool IsExplored() const { return visitCount > 0 && children.size() <= visitCount; }


    /**
     * Creates all legal children for node
     * @param currentBoard Board for this node
     * @return Vector of children created for this node
     */
    std::vector<std::shared_ptr<Node>> Expand(const Board &currentBoard);

    /**
     * @return Children of this node
     */
    const std::vector<std::shared_ptr<Node>> &GetChildren() const { return children; }

    /**
     * Propagates the result of the simulation up the tree
     * @param result Winner of simulation
     * @return Depth the result has been propagated to
     */
    int PropagateResult(Color result);

    /**
     * Goes up the tree and calculates the board this node represents
     * @param rootBoard Board of the tree root
     * @return Board after this node
     */
    Board GetResultingBoard(const Board &rootBoard) const;


    /**
     * @return Average score over all simulations
     */
    double GetScore() const;
};


#endif // CONNECT6_AI_NODE_H
