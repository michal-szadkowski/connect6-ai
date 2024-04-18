#ifndef CONNECT6_AI_CONSOLELOGGER_H
#define CONNECT6_AI_CONSOLELOGGER_H


#include "GameLogger.h"
#include "InfoLogger.h"


/**
 * Class that logs in console format with highlighting moves on board
 */
class ConsoleLogger : public GameLogger, public InfoLogger
{
private:
    int verbosity;

public:
    /**
     *
     * @param verbosity If set to one logs boards, if zero only moves
     */
    ConsoleLogger(int verbosity): verbosity(verbosity) {};

    /**
     * Writes board to stdout with colors and highlighting
     */
    void WriteBoard(const Board& board, const Move& prevMove) override;

    /**
     * Writes move to stdout
     */
    void WriteMove(const Move& move) override;

    /**
     * Writes info to stdout
     */
    void WriteInfo(const std::string& prefix, const std::string& info) override;
};


#endif //CONNECT6_AI_CONSOLELOGGER_H
