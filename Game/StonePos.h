#ifndef CONNECT6_AI_STONEPOS_H
#define CONNECT6_AI_STONEPOS_H

#include <compare>
#include <cstdint>

#define pos_t int8_t

/**
 * Class representing signle stone placed
 */
class StonePos
{
    pos_t x;
    pos_t y;

public:
    /**
     * @return Spectial case representing no stone placed
     */
    static StonePos Empty() { return {}; }

    /**
     * Creates the same object as Empty()
     */
    StonePos() : x(-1), y(-1) {}

    /**
     * Creates new position with given coordinates
     * @param x Row of position
     * @param y Column of position
     */
    StonePos(pos_t x, pos_t y) : x(x), y(y) {}

    /**
     * @return Row of position
     */
    pos_t GetX() const { return x; }

    /**
     * @return Column of position
     */
    pos_t GetY() const { return y; }

    /**
     * Adds two positions together, no guarantee the resulting position is legal
     */
    StonePos operator+(const StonePos &pos) const;
    /**
     * Adds two positions together, no guarantee the resulting position is legal
     */
    StonePos &operator+=(const StonePos &pos);
    /**
     * Compares two positions, first compares rows, then columns
     */
    auto operator<=>(const StonePos &rhs) const = default;
};

#endif // CONNECT6_AI_STONEPOS_H
