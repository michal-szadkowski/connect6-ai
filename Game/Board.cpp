#include <stdexcept>
#include "Board.h"

bool Board::IsEmpty(char x, char y) {
    bool blackBit = black[xy2n(x, y)];
    bool whiteBit = white[xy2n(x, y)];
    return !(blackBit || whiteBit);
}

bool Board::CheckForConnectedAt(char x, char y, Color color) {
    auto &board = color == Black ? black : white;
    bool center = board.test(xy2n(x, y));
    if (!center) return false;

    int h = ConnectedCount<1, 0>(board, x, y);
    h += ConnectedCount<-1, 0>(board, x, y);
    if (h >= 5) return true;

    int v = ConnectedCount<0, 1>(board, x, y);
    v += ConnectedCount<0, -1>(board, x, y);
    if (v >= 5) return true;

    int d1 = ConnectedCount<1, 1>(board, x, y);
    d1 += ConnectedCount<-1, -1>(board, x, y);
    if (d1 >= 5) return true;

    int d2 = ConnectedCount<1, -1>(board, x, y);
    d2 += ConnectedCount<-1, 1>(board, x, y);
    if (d2 >= 5) return true;

    return false;
}


bool Board::Get(char x, char y, Color color) {
    if (color == Black)
        return black[xy2n(x, y)];
    if (color == White)
        return white[xy2n(x, y)];
    return false;
}

void Board::Set(char x, char y, Color color) {
    if (color == Black)
        black.set(xy2n(x, y));
    if (color == White)
        white.set(xy2n(x, y));
    firstMoveMade = true;
}


int Board::xy2n(int x, int y) {
    if (x >= BOARD_SIZE || x < 0)
        throw std::out_of_range("x");
    if (y >= BOARD_SIZE || y < 0)
        throw std::out_of_range("y");
    return x * BOARD_SIZE + y;
}

std::pair<int, int> Board::n2xy(int n) {
    if (n >= BOARD_SIZE * BOARD_SIZE)
        throw std::out_of_range("");
    return {n / BOARD_SIZE, n % BOARD_SIZE};
}

bool Board::withinRange(int x) {
    return x < 19 && x >= 0;
}

bool Board::IsFirstMoveMade() const {
    return firstMoveMade;
}

template<int dx, int dy>
int Board::ConnectedCount(std::bitset<BOARD_SIZE * BOARD_SIZE> &board, char x, char y) {
    char xt = x, yt = y;
    for (int i = 0; i < 5; i++) {
        xt += dx;
        yt += dy;
        if (!(withinRange(xt) && withinRange(yt))) return i;
        bool is = board.test(xy2n(xt, yt));
        if (!is)return i;
    }
    return 5;
}
