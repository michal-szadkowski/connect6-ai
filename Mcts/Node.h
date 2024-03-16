#ifndef CONNECT6_AI_NODE_H
#define CONNECT6_AI_NODE_H

#include <memory>
#include <vector>
#include "../Game/StonePos.h"
#include "../Game/Color.h"

class Node {
private:
    std::weak_ptr<Node> parent;
    std::vector<Node> children;

    StonePos pos;
    Color color;
};


#endif //CONNECT6_AI_NODE_H
