#ifndef CONNECT6_AI_NODE_H
#define CONNECT6_AI_NODE_H

#include <memory>
#include <vector>
#include "../Game/StonePos.h"
#include "../Game/Color.h"
#include "../Game/Board.h"

class Node : public std::enable_shared_from_this<Node> {
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
    Node(std::weak_ptr<Node> parent, StonePos pos, Color color, bool isFirst);
    StonePos GetPosition() const { return pos; }
    Color GetColor() const { return color; }

    double GetValue(double expRate) const;
    unsigned int GetVisitCount() const;

    bool IsExplored() const { return visitCount > 0 && children.size() <= visitCount; }

    std::vector<std::shared_ptr<Node>> Expand(const Board &currentBoard);
    const std::vector<std::shared_ptr<Node>> &GetChildren() const { return children; }
    int PropagateResult(Color result);
    Board GetResultingBoard(const Board &rootBoard) const;
    double GetScore() const;
};


#endif //CONNECT6_AI_NODE_H
