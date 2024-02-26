#ifndef CONNECT6_AI_BOARD_H
#define CONNECT6_AI_BOARD_H

#include <vector>
#include <string>
#include "Move.h"

// assuming 19x19 board
#define BOARD_SIZE 19
#define BOARD_BYTES 46 // ceil(19*19/8)

class Board {
private:
    unsigned char black[BOARD_BYTES];
    unsigned char white[BOARD_BYTES];

    static void MakeSubMove(short movePos, unsigned char colorBoard[BOARD_BYTES]);

    bool IsEmpty(short movePos);

    static std::pair<unsigned char, unsigned char> DecomposeToMajMinOffset(short movePos);

public:
    Board();
    explicit Board(const Board *board);

    bool IsLegal(const Move &move);
    std::vector<Move> GetMoves();
    bool MakeMove(const Move &move);

    Color CheckForEnd();
    Color CheckForEndAfter(Move Move);
};


#endif //CONNECT6_AI_BOARD_H
