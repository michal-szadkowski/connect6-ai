#ifndef CONNECT6_AI_TREE_H
#define CONNECT6_AI_TREE_H

#include <memory>
#include "Node.h"

class Tree {
private:
    Board rootBoard;
public:
    Tree();
    explicit Tree(const Board &board);
    std::shared_ptr<Node> root;


    std::shared_ptr<Node> GetNodeCorrespondingToPos(const StonePos &pos, const Color &col) const;
    void PushMoveToTree(const StonePos &pos, const Color &col);

    std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> GetBestSequence();
    static std::shared_ptr<Node> GetBestFrom(std::vector<std::shared_ptr<Node>> vector);

    std::shared_ptr<Node> Select();
    static std::vector<std::shared_ptr<Node>> FindUnexplored(const std::vector<std::shared_ptr<Node>> &all);
    std::shared_ptr<Node> Expand(const std::shared_ptr<Node> &node);


    Board GetBoardForNode(const std::shared_ptr<Node> &node) const { return node->GetResultingBoard(rootBoard); }
};


#endif //CONNECT6_AI_TREE_H
