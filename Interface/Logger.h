#ifndef CONNECT6_AI_LOGGER_H
#define CONNECT6_AI_LOGGER_H


#include "../Game/Board.h"


class Logger {
public:
    virtual void WriteBoard(const Board &board, const Move &prevMove) {};
    virtual void WriteMove(const Move &move) {};
    virtual void WriteInfo(const std::string &info) {};
    std::string WriteColor(const Color &color) {
        if (color == Color::Black) return "black";
        else if (color == Color::White) return "white";
        else if (color == Color::Draw)return "draw";
        return "none";
    };
};

#endif //CONNECT6_AI_LOGGER_H