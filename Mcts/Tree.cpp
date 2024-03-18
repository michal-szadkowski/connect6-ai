#include "Tree.h"

bool Tree::PromoteToRoot(const Node &node) {
    return false;
}

Tree::Tree() : Tree(Board()) {
}

Tree::Tree(const Board &board) {
    rootBoard = board;
    Color col = !board.ExpectingHalfMove() ? board.GetTurn() : Reverse(board.GetTurn());
    root = std::make_shared<Node>(std::weak_ptr<Node>(), StonePos::Empty(), col, !board.ExpectingHalfMove());
}

std::shared_ptr<Node> Tree::Select() {
    std::shared_ptr<Node> current = root;
    while (true) {
        auto children = current->GetChildren();
        if (children.empty()) return current;
        std::shared_ptr<Node> max;
        for (const auto &n: children) {
            if (max == nullptr || n->GetValue() > max->GetValue()) {
                max = n;
            }
        }
        current = max;
    }
}
std::vector<std::shared_ptr<Node>> Tree::Expand(const std::shared_ptr<Node> &node) {
    auto b = node->GetResultingBoard(rootBoard);
    return node->Expand(b);
}
