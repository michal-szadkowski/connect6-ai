#ifndef CONNECT6_AI_MOVE_H
#define CONNECT6_AI_MOVE_H


#include "Color.h"

struct Move {
public:
    char x1;
    char y1;
    char x2;
    char y2;

    Color color;

    Move(char x1, char y1, char x2, char y2, Color color);
};


#endif //CONNECT6_AI_MOVE_H
