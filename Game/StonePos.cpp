#include "StonePos.h"

StonePos StonePos::operator+(const StonePos &pos) const {
    return {static_cast<pos_t>(x + pos.x), static_cast<pos_t>(y + pos.y)};
}

StonePos &StonePos::operator+=(const StonePos &pos) {
    *this = *this + pos;
    return *this;
}