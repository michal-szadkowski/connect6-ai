#ifndef CONNECT6_AI_CONSOLELOGGER_H
#define CONNECT6_AI_CONSOLELOGGER_H


#include "FileLogger.h"
#include "GameLogger.h"


/**
 * Class that logs in console format with highlighting moves on board
 */
class ConsoleLogger : public FileLogger
{
protected:
    /**
     * Writes formatted piece, using color to highlight previous move
     */
    void WritePiece(Color piece, bool isFromPrevMove) override;

public:
    ConsoleLogger(int verbosity) : FileLogger(verbosity){};
};


#endif // CONNECT6_AI_CONSOLELOGGER_H
