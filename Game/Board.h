#ifndef CONNECT6_AI_BOARD_H
#define CONNECT6_AI_BOARD_H

#include <bitset>
#include <string>
#include <vector>
#include "Move.h"

// assuming 19x19 board
#define BOARD_SIZE 19


class Board
{
private:
    std::bitset<BOARD_SIZE * BOARD_SIZE> black;
    std::bitset<BOARD_SIZE * BOARD_SIZE> white;
    int stonesPlaced = 0;

    Color turn = Color::Black;
    Color result = Color::None;

    static int xy2n(const StonePos &pos);

    template <int dx, int dy>
    int ConnectedCount(const std::bitset<BOARD_SIZE * BOARD_SIZE> &board, const StonePos &pos) const;
    bool CheckForConnectedAt(const StonePos &pos, Color color) const;

    Color CheckWinAfter(const StonePos &pos, Color color) const;

    void ChangeTurn();

    void Set(const StonePos &pos, Color color);

public:
    std::vector<StonePos> GetAllEmpty() const;

    bool IsEmpty(const StonePos &pos) const;

        bool Get(const StonePos &pos, Color color) const;
        Color PutStone(const StonePos &pos, Color stoneColor);

        Color GetTurn() const;
        Color GetResult() const;

        int StonesPlacedCount() const;
        bool ExpectingFullMove() const;
};


#endif // CONNECT6_AI_BOARD_H
