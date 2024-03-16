#include "Node.h"

#include <memory>

Node::Node(std::weak_ptr<Node> parent, StonePos pos, Color color, bool isFirst) :
        parent(std::move(parent)), pos(pos), color(color), isFirstOfMove(isFirst) {
}

std::vector<std::shared_ptr<Node>> Node::Expand(Board currentBoard) {
    if (!children.empty()) return children;
    auto positions = currentBoard.GetAllEmpty();
    Color nextColor = isFirstOfMove ? color : Reverse(color);
    for (auto p: positions) {
        children.emplace_back(std::make_shared<Node>(shared_from_this(), p, nextColor, !isFirstOfMove));
    }
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
    return 1;
}
