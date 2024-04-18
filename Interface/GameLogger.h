#ifndef CONNECT6_AI_GAMELOGGER_H
#define CONNECT6_AI_GAMELOGGER_H


#include "../Game/Board.h"


/**
 * Interface for logging game status like position and moves
 */
class GameLogger
{
protected:
    /**
     * @return String representation of Color enum
     */
    static std::string WriteColor(const Color &color)
    {
        if (color == Color::Black)
            return "black";
        if (color == Color::White)
            return "white";
        if (color == Color::Draw)
            return "draw";
        return "none";
    };

public:
    /**
     * @param board Current board
     * @param prevMove Move made before current position was reached, may be used to highlight positions
     */
    virtual void WriteBoard(const Board &board, const Move &prevMove) = 0;
    /**
     * @param move Move to write
     */
    virtual void WriteMove(const Move &move) = 0;

    virtual ~GameLogger() = default;
};

#endif // CONNECT6_AI_GAMELOGGER_H
