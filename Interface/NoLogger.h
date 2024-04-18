#ifndef NOLOGGER_H
#define NOLOGGER_H
#include "ConsoleLogger.h"


/**
 * Logger that does not log anything, used in internal simulations
 */
class NoLogger final : public InfoLogger, public GameLogger
{
public:
    NoLogger() {}
    void WriteBoard(const Board &board, const Move &prevMove) override{};
    void WriteMove(const Move &move) override{};
    void WriteInfo(const std::string &name, const std::string &info) override{};
};

#endif // NOLOGGER_H
