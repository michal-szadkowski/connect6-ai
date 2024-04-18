#ifndef CONNECT6_AI_BOARD_H
#define CONNECT6_AI_BOARD_H

#include <bitset>
#include <string>
#include <vector>
#include "Move.h"

// assuming 19x19 board
#define BOARD_SIZE 19

/**
 * Represents the board of connect6
 */
class Board
{
private:
    std::bitset<BOARD_SIZE * BOARD_SIZE> black;
    std::bitset<BOARD_SIZE * BOARD_SIZE> white;
    int stonesPlaced = 0;

    Color turn = Color::Black;
    Color result = Color::None;

    /**
     * Converts StonePos to single dimenstion position
     * @return Index of the square
     */
    static int xy2n(const StonePos &pos);

    /**
     * Calculates amount of stone connected in a given direction
     * @tparam dx Direction in x
     * @tparam dy Direction in y
     * @param board Single colored board
     * @param pos Position to check from
     * @return Amount of connected stones in given direciton
     */
    template <int dx, int dy>
    int ConnectedCount(const std::bitset<BOARD_SIZE * BOARD_SIZE> &board, const StonePos &pos) const;
    /**
     * Checks if there are at least 6 stones connected in a row including given position
     */
    bool CheckForConnectedAt(const StonePos &pos, Color color) const;

    /**
     * Checks if there is a result of the game
     * @param pos Position that may have changed the result
     * @param color Color of stone placed in position
     * @return Color of winner or draw, if there is no winner returns None
     */
    Color CheckWinAfter(const StonePos &pos, Color color) const;

    /**
     * Changes turn of the board
     */
    void ChangeTurn();

    /**
     * Sets stone in given position, does not check for legallity
     */
    void Set(const StonePos &pos, Color color);

public:
    /**
     * @return All empty positions from current board
     */
    std::vector<StonePos> GetAllEmpty() const;

    /**
     * @return True if given position is empty
     */
    bool IsEmpty(const StonePos &pos) const;

    /**
     * @return True if on a given position there is a stone of given color
     */
    bool Get(const StonePos &pos, Color color) const;
    /**
     * Places a stone of given color in a given position, checks if the color matches the turn
     * @return Winner after placing move, if there is no winner returns None
     */
    Color PutStone(const StonePos &pos, Color stoneColor);

    /**
     * @return Color of current turn
     */
    Color GetTurn() const;
    /**
     * @return Result after last stone placed
     */
    Color GetResult() const;

    /**
     *
     * @return Amount of all stones placed on the board
     */
    int StonesPlacedCount() const;
    /**
     *
     * @return True if board is expecting two stone positions as next move
     */
    bool ExpectingFullMove() const;
};


#endif // CONNECT6_AI_BOARD_H
