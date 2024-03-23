#include <algorithm>
#include "Tree.h"
#include "../Random.h"

Tree::Tree() : Tree(Board()) {
}

Tree::Tree(const Board &board) {
    rootBoard = board;
    Color col = board.ExpectingFullMove() ? Reverse(board.GetTurn()) : board.GetTurn();
    root = std::make_shared<Node>(std::weak_ptr<Node>(), StonePos::Empty(), col, !board.ExpectingFullMove());
}


std::shared_ptr<Node> Tree::GetNodeCorrespondingToPos(const StonePos &pos, const Color &col) const {
    for (const auto &i: root->GetChildren())
        if (i->GetPosition() == pos && i->GetColor() == col)
            return i;
    return {nullptr};
}

void Tree::PushMoveToTree(const StonePos &pos, const Color &col) {
    auto existing = GetNodeCorrespondingToPos(pos, col);
    if (existing.get()) {
        root = std::move(existing);
    } else {
        root = std::make_shared<Node>(std::weak_ptr<Node>(), pos, col, rootBoard.ExpectingFullMove());
    }
    rootBoard.PutStone(pos, col);
}

std::shared_ptr<Node> Tree::Select() {
    std::shared_ptr<Node> current = root;
    while (true) {
        auto children = current->GetChildren();
        std::shuffle(children.begin(), children.end(), Random::getGen());
        if (children.empty()) return current;
        auto unexplored = FindUnexplored(children);
        if (!unexplored.empty()) return current;
        std::shared_ptr<Node> max;
        for (const auto &n: children) {
            if (max == nullptr || n->GetValue() > max->GetValue()) {
                max = n;
            }
        }
        current = max;
    }
}

std::vector<std::shared_ptr<Node>> Tree::FindUnexplored(const std::vector<std::shared_ptr<Node>> &all) {
    std::vector<std::shared_ptr<Node>> result;
    for (const auto &item: all) {
        if (item->GetValue() == std::numeric_limits<double>::infinity())
            result.push_back(item);
    }
    return result;
}

std::shared_ptr<Node> Tree::Expand(const std::shared_ptr<Node> &node) {
    auto b = node->GetResultingBoard(rootBoard);
    auto children = node->Expand(b);
    if (children.empty())
        return node;
    auto unexplored = FindUnexplored(children);
    if (unexplored.empty())
        return Random::SelectRandomElement(children);
    else
        return Random::SelectRandomElement(unexplored);
}

std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> Tree::GetBestSequence() {
    std::shared_ptr<Node> first, second;
    auto ch1 = root->GetChildren();
    first = ch1.front();
    for (const auto &item: ch1) {
        if (item->GetWinRate() > first->GetWinRate() && !item->GetChildren().empty())
            first = item;
    }
    if (first->GetColor() == first->GetChildren().front()->GetColor())
        second = GetBestFrom(first->GetChildren());
    return {first, second};
}

std::shared_ptr<Node> Tree::GetBestFrom(std::vector<std::shared_ptr<Node>> vector) {
    std::shared_ptr<Node> result = vector.front();
    for (const auto &item: vector) {
        if (item->GetWinRate() > result->GetWinRate())
            result = item;
    }
    return result;
}
