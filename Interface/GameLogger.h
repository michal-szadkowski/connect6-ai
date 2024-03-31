#ifndef CONNECT6_AI_GAMELOGGER_H
#define CONNECT6_AI_GAMELOGGER_H


#include "../Game/Board.h"


class GameLogger {
public:
    virtual void
    WriteBoard(__attribute__((unused)) const Board &board, __attribute__((unused)) const Move &prevMove) {};
    virtual void WriteMove(__attribute__((unused)) const Move &move) {};
    static std::string WriteColor(const Color &color) {
        if (color == Color::Black) return "black";
        else if (color == Color::White) return "white";
        else if (color == Color::Draw)return "draw";
        return "none";
    };
    virtual ~GameLogger() = default;
};

#endif //CONNECT6_AI_GAMELOGGER_H