#ifndef CONNECT6_AI_STONEPOS_H
#define CONNECT6_AI_STONEPOS_H

#include <compare>
#include <cstdint>

#define pos_t int8_t

class StonePos {
    pos_t x;
    pos_t y;
public:
    static StonePos Empty() { return {}; }

    StonePos() : x(-1), y(-1) {}

    StonePos(pos_t x, pos_t y) : x(x), y(y) {}

    pos_t GetX() const { return x; }

    pos_t GetY() const { return y; }

    StonePos operator+(const StonePos &pos) const;
    StonePos &operator+=(const StonePos &pos);
    auto operator<=>(const StonePos &rhs) const = default;
};

#endif //CONNECT6_AI_STONEPOS_H
