#ifndef FILELOGGER_H
#define FILELOGGER_H
#include "GameLogger.h"
#include "InfoLogger.h"


class FileLogger : public GameLogger, public InfoLogger
{
protected:
    int verbosity;

    /**
     * Writes unformatted piece to stdout
     */
    virtual void WritePiece(Color piece, bool isFromPrevMove);

public:
    /**
     *
     * @param verbosity If set to one logs boards, if zero only moves
     */
    FileLogger(int verbosity) : verbosity(verbosity){};

    /**
     * Writes board to stdout with colors and highlighting
     */
    void WriteBoard(const Board &board, const Move &prevMove) override;

    /**
     * Writes move to stdout
     */
    void WriteMove(const Move &move) override;

    /**
     * Writes info to stdout
     */
    void WriteInfo(const std::string &prefix, const std::string &info) override;
};


#endif // FILELOGGER_H
