#include "Board.h"


Board::Board() : black(), white() {
}

Board::Board(const Board *board) : Board() {
    for (int i = 0; i < BOARD_BYTES; i++) {
        this->black[i] = board->black[i];
        this->white[i] = board->white[i];
    }
}

bool Board::IsLegal(const Move &move) {
    if (move.first == move.second) return false;
    if (move.first >= BOARD_SIZE * BOARD_SIZE || move.second >= BOARD_SIZE * BOARD_SIZE) return false;
    return IsEmpty(move.first) && IsEmpty(move.second);
}


std::vector<Move> Board::GetMoves() {
    //TODO
    return std::vector<Move>();
}

bool Board::MakeMove(const Move &move) {
    if (!IsLegal(move))
        return false;
    unsigned char *board = move.color == Black ? black : white;
    MakeSubMove(move.first, board);
    MakeSubMove(move.second, board);
    return true;
}

void Board::MakeSubMove(short movePos, unsigned char colorBoard[BOARD_BYTES]) {
    auto offset = DecomposeToMajMinOffset(movePos);
    unsigned char one = 1;
    colorBoard[offset.first] |= one << offset.second;
}

bool Board::IsEmpty(short movePos) {
    auto offset = DecomposeToMajMinOffset(movePos);
    bool blackEmpty = black[offset.first] >> offset.second == 0;
    bool whiteEmpty = white[offset.first] >> offset.second == 0;
    return whiteEmpty && blackEmpty;
}

std::pair<unsigned char, unsigned char> Board::DecomposeToMajMinOffset(short movePos) {
    int primary = movePos / 8;
    int secondary = 7 - (movePos % 8);
    return {primary, secondary};
}

Color Board::CheckForEnd() {
    return White;
}

Color Board::CheckForEndAfter(Move Move) {
    auto offset = DecomposeToMajMinOffset(Move.first);
    return White;
}

