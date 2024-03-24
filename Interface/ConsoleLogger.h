#ifndef CONNECT6_AI_CONSOLELOGGER_H
#define CONNECT6_AI_CONSOLELOGGER_H


#include "Logger.h"

class ConsoleLogger : public Logger {
public:
    void WriteBoard(const Board &board, const Move &prevMove) override;
    void WriteMove(const Move &move) override;
    void WriteInfo(const std::string &info) override;
};


#endif //CONNECT6_AI_CONSOLELOGGER_H
