#ifndef CONNECT6_AI_CONSOLELOGGER_H
#define CONNECT6_AI_CONSOLELOGGER_H


#include "FileLogger.h"
#include "GameLogger.h"


class ConsoleLogger : public FileLogger
{
protected:
        void WritePiece(Color piece, bool isFromPrevMove) override;

public:
    ConsoleLogger(int verbosity) : FileLogger(verbosity){};
};


#endif // CONNECT6_AI_CONSOLELOGGER_H
