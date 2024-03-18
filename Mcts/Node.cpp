#include "Node.h"

#include <limits>
#include <memory>

Node::Node(std::weak_ptr<Node> parent, StonePos pos, Color color, bool isFirst) :
        parent(std::move(parent)), pos(pos), color(color), isFirstOfMove(isFirst) {
}

std::vector<std::shared_ptr<Node>> Node::Expand(Board currentBoard) {
    if (expanded) return children;
    auto positions = currentBoard.GetAllEmpty();
    Color nextColor = isFirstOfMove ? color : Reverse(color);
    for (auto p: positions) {
        children.emplace_back(std::make_shared<Node>(shared_from_this(), p, nextColor, !isFirstOfMove));
    }
    expanded = true;
    return children;
}


Board Node::GetResultingBoard(Board rootBoard) const {
    Board b = rootBoard;
    if (auto p = parent.lock()) {
        b = p->GetResultingBoard(b);
    }
    if (pos != StonePos::Empty())
        b.Set(pos, color);
    return b;
}

double Node::GetValue() const {
    if (visitCount == 0)
        return std::numeric_limits<double>::infinity();
    return score * 1.0 / visitCount;
}
int Node::Propagate(Color result) {
    ++visitCount;
    if (color == result) ++score;
    else if (color == Reverse(result)) --score;
    int depth = 0;
    if (auto p = parent.lock()) {
        depth = p->Propagate(result);
    }
    return depth + 1;
}
