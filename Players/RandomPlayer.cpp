#include <random>
#include "RandomPlayer.h"

Move RandomPlayer::GetMove(const Board &board, const Move &prevMove) {
    auto pos1 = GetRandomPos(board, StonePos::Empty());
    if (board.StonesPlacedCount() == 0)
        return {pos1, StonePos::Empty(), this->GetColor()};
    else {
        auto pos2 = GetRandomPos(board, pos1);
        return {pos1, pos2, this->GetColor()};
    }
}

StonePos RandomPlayer::GetRandomPos(const Board &board, StonePos prev) {
    char x, y;
    do {
        x = static_cast<char>(rng());
        y = static_cast<char>(rng());
    } while (!board.IsEmpty({x, y}) || prev == StonePos(x, y));
    return {x, y};
}

RandomPlayer::RandomPlayer() {
    std::random_device randomDevice;
    std::mt19937 mt(randomDevice());
    std::uniform_int_distribution<int> d(0, BOARD_SIZE - 1);
    this->rng = [d, mt] mutable { return d(mt); };
}

