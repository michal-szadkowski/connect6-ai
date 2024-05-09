#ifndef CONNECT6_AI_MOVE_H
#define CONNECT6_AI_MOVE_H


#include "Color.h"
#include "StonePos.h"

class Move
{
private:
    StonePos first;
    StonePos second;
    Color color;

public:
    Move(StonePos first, Color color) : first(first), second(StonePos::Empty()), color(color) {}

    Move(StonePos first, StonePos second, Color color) : first(first), second(second), color(color) {}
    const StonePos &GetFirst() const { return first; }
    const StonePos &GetSecond() const { return second; }
    Color GetColor() const { return color; }

    bool IsHalf() const { return second == StonePos::Empty(); }
};


#endif // CONNECT6_AI_MOVE_H
