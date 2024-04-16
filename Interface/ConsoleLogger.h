#ifndef CONNECT6_AI_CONSOLELOGGER_H
#define CONNECT6_AI_CONSOLELOGGER_H


#include "GameLogger.h"
#include "InfoLogger.h"

class ConsoleLogger : public GameLogger, public InfoLogger
{
private:
    int verbosity;

public:
    ConsoleLogger(int verbosity): verbosity(verbosity) {};
    void WriteBoard(const Board& board, const Move& prevMove) override;
    void WriteMove(const Move& move) override;
    void WriteInfo(const std::string& prefix, const std::string& info) override;
};


#endif //CONNECT6_AI_CONSOLELOGGER_H
