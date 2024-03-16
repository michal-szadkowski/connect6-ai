#ifndef CONNECT6_AI_TREE_H
#define CONNECT6_AI_TREE_H

#include <memory>
#include "Node.h"

class Tree {
private:
    std::unique_ptr<Node> root;
    bool PromoteToRoot(const Node &node);
    
};


#endif //CONNECT6_AI_TREE_H
