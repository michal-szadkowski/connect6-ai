#ifndef CONNECT6_AI_MOVE_H
#define CONNECT6_AI_MOVE_H


#include "Color.h"
#include "StonePos.h"

/**
 * Represents full move
 */
class Move {
private:
    StonePos first;
    StonePos second;
    Color color;
public:
    /**
     * Creates move from only one position, only for first move on the board or if the move ends with a win.
     */
    Move(StonePos first, Color color) : first(first), second(StonePos::Empty()), color(color) {}

    /**
     * Creates move from two positions
     */
    Move(StonePos first, StonePos second, Color color) : first(first), second(second), color(color) {}
    /**
     * @return First position of the move
     */
    const StonePos &GetFirst() const { return first; }
    /**
     *
     * @return Second position of the move, may be StonePos::Empty()
     */
    const StonePos &GetSecond() const { return second; }
    /**
     * @return Color of the move
     */
    Color GetColor() const { return color; }

    /**
     *
     * @return Wheather move consists of only one position
     */
    bool IsHalf() const { return second == StonePos::Empty(); }
    
};


#endif //CONNECT6_AI_MOVE_H
