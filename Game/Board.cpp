#include <stdexcept>
#include "Board.h"

bool Board::IsEmpty(const StonePos &pos) const {
    bool blackBit = black[xy2n(pos)];
    bool whiteBit = white[xy2n(pos)];
    return !(blackBit || whiteBit);
}

bool Board::Get(const StonePos &pos, Color color) const {
    if (color == Color::Black)
        return black[xy2n(pos)];
    if (color == Color::White)
        return white[xy2n(pos)];
    return false;
}

void Board::Set(const StonePos &pos, Color color) {
    if (color == Color::Black)
        black.set(xy2n(pos));
    if (color == Color::White)
        white.set(xy2n(pos));
    ++stonesPlaced;
}

Color Board::PutStone(const StonePos &pos, Color stoneColor) {
    if (stoneColor != turn)
        throw std::invalid_argument("color");
    Set(pos, stoneColor);
    if (ExpectingFullMove())
        ChangeTurn();

    Color win = CheckWinAfter(pos, stoneColor);
    if (win != Color::None) {
        result = win;
        turn = Color::None;
    }
    return result;
}

int Board::StonesPlacedCount() const {
    return stonesPlaced;
}

bool Board::ExpectingFullMove() const {
    return StonesPlacedCount() % 2;
}

Color Board::GetTurn() const {
    return turn;
}
void Board::ChangeTurn() {
    turn = Reverse(turn);
}


std::vector<StonePos> Board::GetAllEmpty() const {
    auto b = black | white;
    std::vector<StonePos> empty;
    for (char i = 0; i < BOARD_SIZE; ++i) {
        for (char j = 0; j < BOARD_SIZE; ++j) {
            if (!b[xy2n({i, j})])
                empty.emplace_back(i, j);
        }
    }
    return empty;
}


Color Board::CheckWinAfter(const StonePos &pos, Color color) const {
    if (StonesPlacedCount() == BOARD_SIZE * BOARD_SIZE) {
        return Color::Draw;
    }
    if (CheckForConnectedAt(pos, color)) {
        return color;
    }
    return Color::None;
}

bool Board::CheckForConnectedAt(const StonePos &pos, Color color) const {
    auto &board = color == Color::Black ? black : white;
    bool center = board.test(xy2n(pos));
    if (!center) return false;

    int h = ConnectedCount<1, 0>(board, pos);
    h += ConnectedCount<-1, 0>(board, pos);
    if (h >= 5) return true;

    int v = ConnectedCount<0, 1>(board, pos);
    v += ConnectedCount<0, -1>(board, pos);
    if (v >= 5) return true;

    int d1 = ConnectedCount<1, 1>(board, pos);
    d1 += ConnectedCount<-1, -1>(board, pos);
    if (d1 >= 5) return true;

    int d2 = ConnectedCount<1, -1>(board, pos);
    d2 += ConnectedCount<-1, 1>(board, pos);
    if (d2 >= 5) return true;

    return false;
}

bool InBoard(const StonePos &pos) {
    if (pos.GetX() < 0 || pos.GetX() >= BOARD_SIZE) return false;
    if (pos.GetY() < 0 || pos.GetY() >= BOARD_SIZE) return false;
    return true;
}

template<int dx, int dy>
int Board::ConnectedCount(const std::bitset<BOARD_SIZE * BOARD_SIZE> &board, const StonePos &pos) const {
    StonePos p = pos;
    for (int i = 0; i < 5; i++) {
        p += {dx, dy};
        if (!InBoard(p)) return i;
        bool is = board.test(xy2n(p));
        if (!is)return i;
    }
    return 5;
}

int Board::xy2n(const StonePos &pos) {
    if (pos.GetX() >= BOARD_SIZE || pos.GetX() < 0)
        throw std::out_of_range("x");
    if (pos.GetY() >= BOARD_SIZE || pos.GetY() < 0)
        throw std::out_of_range("y");
    return pos.GetX() * BOARD_SIZE + pos.GetY();
}
Color Board::GetResult() const {
    return result;
}
