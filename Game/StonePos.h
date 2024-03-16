#ifndef CONNECT6_AI_STONEPOS_H
#define CONNECT6_AI_STONEPOS_H

#include <compare>

class StonePos {
    char x;
    char y;
public:
    static StonePos Empty() { return {}; }

    StonePos() : x(-1), y(-1) {}

    StonePos(char x, char y) : x(x), y(y) {}

    char GetX() const { return x; }

    char GetY() const { return y; }

    StonePos operator+(const StonePos &pos) const;
    StonePos &operator+=(const StonePos &pos);
    auto operator<=>(const StonePos &rhs) const = default;
};

#endif //CONNECT6_AI_STONEPOS_H
