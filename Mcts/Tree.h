#ifndef CONNECT6_AI_TREE_H
#define CONNECT6_AI_TREE_H

#include <memory>
#include "Node.h"

class Tree {
private:
    std::shared_ptr<Node> root;
    Board rootBoard;
public:
    Tree();
    Tree(const Board &board);

    bool PromoteToRoot(const Node &node);

    std::shared_ptr<Node> Select();
    std::vector<std::shared_ptr<Node>> Expand(const std::shared_ptr<Node> &node);

    std::pair<StonePos, StonePos> GetBest();

    Board GetBoardForNode(const std::shared_ptr<Node> node) const { return node->GetResultingBoard(rootBoard); }
};


#endif //CONNECT6_AI_TREE_H
