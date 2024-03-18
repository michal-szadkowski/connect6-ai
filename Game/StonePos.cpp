#include "StonePos.h"

StonePos StonePos::operator+(const StonePos &pos) const {
    return {static_cast<char>(x + pos.x), static_cast<char>(y + pos.y)};
}

StonePos &StonePos::operator+=(const StonePos &pos) {
    *this = *this + pos;
    return *this;
}

//TODO comparing
