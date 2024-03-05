#ifndef CONNECT6_AI_BOARD_H
#define CONNECT6_AI_BOARD_H

#include <vector>
#include <string>
#include <bitset>
#include "Move.h"

// assuming 19x19 board
#define BOARD_SIZE 19

class Board {
private:
    std::bitset<BOARD_SIZE * BOARD_SIZE> black;
    std::bitset<BOARD_SIZE * BOARD_SIZE> white;
    bool firstMoveMade = false;

    static int xy2n(int x, int y);
    static std::pair<int, int> n2xy(int n);
    static bool withinRange(int x);

    template<int dx, int dy>
    int ConnectedCount(std::bitset<BOARD_SIZE * BOARD_SIZE> &board, char x, char y); //loop unrolling
public:
    Board() = default;
    Board(const Board &board) = default;

    bool Get(char x, char y, Color color);
    void Set(char x, char y, Color color);

    bool CheckForConnectedAt(char x, char y, Color color);

    bool IsEmpty(char x, char y);
    bool IsFirstMoveMade() const;
};


#endif //CONNECT6_AI_BOARD_H
