#ifndef CONNECT6_AI_MOVE_H
#define CONNECT6_AI_MOVE_H


#include "Color.h"
#include "StonePos.h"

class Move {
public:
    StonePos first;
    StonePos second;
    Color color;

    Move(StonePos first, StonePos second, Color color) : first(first), second(second), color(color) {}
};


#endif //CONNECT6_AI_MOVE_H
