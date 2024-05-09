#ifndef FILELOGGER_H
#define FILELOGGER_H
#include "GameLogger.h"
#include "InfoLogger.h"


class FileLogger : public GameLogger, public InfoLogger
{
protected:
    int verbosity;

        virtual void WritePiece(Color piece, bool isFromPrevMove);

public:
        FileLogger(int verbosity) : verbosity(verbosity){};

        void WriteBoard(const Board &board, const Move &prevMove) override;

        void WriteMove(const Move &move) override;

        void WriteInfo(const std::string &prefix, const std::string &info) override;
};


#endif // FILELOGGER_H
