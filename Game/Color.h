#ifndef CONNECT6_AI_COLOR_H
#define CONNECT6_AI_COLOR_H

enum class Color : char {
    None = 0,
    Black = 1,
    White = -1,
    Draw = 2
};

constexpr Color Reverse(Color c) {
    if (c == Color::White)
        return Color::Black;
    else if (c == Color::Black)
        return Color::White;
    return c;
}


#endif //CONNECT6_AI_COLOR_H
