#ifndef CONNECT6_AI_NODE_H
#define CONNECT6_AI_NODE_H

#include <memory>
#include <vector>
#include "../Game/StonePos.h"
#include "../Game/Color.h"
#include "../Game/Board.h"

class Node : public std::enable_shared_from_this<Node> {
private:
    std::weak_ptr<Node> parent;
    std::vector<std::shared_ptr<Node>> children;
    bool expanded = false;

    StonePos pos;
    Color color;
    bool isFirstOfMove;

    int visitCount = 0;
    int score = 0;
public:
    Node(std::weak_ptr<Node> parent, StonePos pos, Color color, bool isFirst);
    StonePos GetPosition() const { return pos; }
    Color GetColor() const { return color; }

    double GetValue() const;
    double GetVisitCount() const { return visitCount; }

    bool IsExpanded() const { return expanded; }

    std::vector<std::shared_ptr<Node>> Expand(Board currentBoard);
    std::vector<std::shared_ptr<Node>> GetChildren() const { return children; }
    int Propagate(Color result);
    Board GetResultingBoard(Board rootBoard) const;


};


#endif //CONNECT6_AI_NODE_H
