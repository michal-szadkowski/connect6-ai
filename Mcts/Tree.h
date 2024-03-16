#ifndef CONNECT6_AI_TREE_H
#define CONNECT6_AI_TREE_H

#include <memory>
#include "Node.h"

class Tree {
private:
    std::shared_ptr<Node> root;
    Board rootBoard;
public:
    Tree(const Board &board);

    bool PromoteToRoot(const Node &node);

    std::shared_ptr<Node> Select();
    
};


#endif //CONNECT6_AI_TREE_H
