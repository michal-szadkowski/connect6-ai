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
    int stonesPlaced = 0;

    static int xy2n(const StonePos &pos);
    template<int dx, int dy>
    int ConnectedCount(const std::bitset<BOARD_SIZE * BOARD_SIZE> &board, const StonePos &pos) const;
public:
    Board() = default;
    Board(const Board &board) = default;

    std::vector<StonePos> GetAllEmpty() const;
    bool IsEmpty(const StonePos &pos) const;
    bool Get(const StonePos &pos, Color color) const;
    void Set(const StonePos &pos, Color color);

    bool CheckForConnectedAt(const StonePos &pos, Color color) const;
    Color CheckWinAfter(const StonePos &pos, Color color) const;

    int StonesPlacedCount() const;
};


#endif //CONNECT6_AI_BOARD_H
