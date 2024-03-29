#include <random>
#include "RandomPlayer.h"
#include "../Random.h"

Move RandomPlayer::GetMove(const Board &board, const Move &prevMove) {
    auto pos1 = GetRandomPos(board, StonePos::Empty());
    if (!board.ExpectingFullMove())
        return {pos1, StonePos::Empty(), this->GetColor()};
    else {
        auto pos2 = GetRandomPos(board, pos1);
        return {pos1, pos2, this->GetColor()};
    }
}

StonePos RandomPlayer::GetRandomPos(const Board &board, StonePos prev) {
    pos_t x, y;
    do {
        x = static_cast<pos_t>(Random::RandomInRange(0, BOARD_SIZE));
        y = static_cast<pos_t>(Random::RandomInRange(0, BOARD_SIZE));
    } while (!board.IsEmpty({x, y}) || prev == StonePos(x, y));
    return {x, y};
}
