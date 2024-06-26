#ifndef CONNECT6_AI_TREE_H
#define CONNECT6_AI_TREE_H

#include <memory>
#include "Node.h"

class Tree
{
private:
    Board rootBoard;
    std::shared_ptr<Node> root;


        std::shared_ptr<Node> GetNodeCorrespondingToPos(const StonePos &pos, const Color &col) const;

        static std::shared_ptr<Node> GetBestFrom(std::vector<std::shared_ptr<Node>> vector);


        static std::vector<std::shared_ptr<Node>> FindUnexplored(const std::vector<std::shared_ptr<Node>> &all);

public:
        Tree();

        explicit Tree(const Board &board);


        void PushMoveToTree(const StonePos &pos, const Color &col);

        std::shared_ptr<Node> GetRoot() { return root; }


        std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> GetBestSequence();


        std::shared_ptr<Node> SelectLeaf(double expRate) const;

        std::shared_ptr<Node> ExpandAndGetForSimulation(const std::shared_ptr<Node> &node);


        Board GetBoardForNode(const std::shared_ptr<Node> &node) const;
};


#endif // CONNECT6_AI_TREE_H
