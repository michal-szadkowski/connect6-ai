#ifndef CONNECT6_AI_COLOR_H
#define CONNECT6_AI_COLOR_H

#include <cstdint>

/**
 * Represents color of the player, move and result of the game
 */
enum class Color : int8_t {
    None = 0,
    Black = 1,
    White = -1,
    Draw = 2
};

/**
 * Reverses the color, only reverses black and white
 * @param c Color to reverse
 * @return Reverse of c
 */
constexpr Color Reverse(Color c) {
    if (c == Color::White)
        return Color::Black;
    else if (c == Color::Black)
        return Color::White;
    return c;
}


#endif //CONNECT6_AI_COLOR_H
