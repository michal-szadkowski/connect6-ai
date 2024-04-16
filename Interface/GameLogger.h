#ifndef CONNECT6_AI_GAMELOGGER_H
#define CONNECT6_AI_GAMELOGGER_H


#include "../Game/Board.h"


class GameLogger
{
public:
    virtual void WriteBoard(const Board& board, const Move& prevMove) = 0;
    virtual void WriteMove(const Move& move) = 0;

    static std::string WriteColor(const Color& color)
    {
        if (color == Color::Black)
            return "black";
        if (color == Color::White)
            return "white";
        if (color == Color::Draw)
            return "draw";
        return "none";
    };
    virtual ~GameLogger() = default;
    GameLogger() = default;
};

#endif //CONNECT6_AI_GAMELOGGER_H
