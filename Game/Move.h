#ifndef CONNECT6_AI_MOVE_H
#define CONNECT6_AI_MOVE_H


#include "Color.h"

struct Move {
public:
    short first;
    short second;

    Color color;

    Move(short first, short second, Color color);
};


#endif //CONNECT6_AI_MOVE_H
