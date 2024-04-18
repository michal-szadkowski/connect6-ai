#include "FileLogger.h"
#include <format>
#include <iostream>

void FileLogger::WriteMove(const Move &move)
{
    if (move.GetFirst() != StonePos::Empty())
        std::cout << std::format("[{:d} {:d}]", move.GetFirst().GetX(), move.GetFirst().GetY());
    if (move.GetSecond() != StonePos::Empty())
        std::cout << std::format(" [{:d} {:d}]", move.GetSecond().GetX(), move.GetSecond().GetY());
    std::cout << std::endl;
}

void FileLogger::WritePiece(Color piece, bool isFromPrevMove)
{
    std::string s = ".";
    if (piece == Color::White)
        s = "X";
    if (piece == Color::Black)
        s = "O";
    ;
    std::cout << s << " ";
}
void FileLogger::WriteBoard(const Board &board, const Move &prevMove)
{
    if (verbosity > 0)
    {
        std::cout << std::endl;

        std::cout << "  ";
        for (int i = 0; i < BOARD_SIZE; ++i)
        {
            if (i >= 10)
                std::cout << std::format("{:2d}", i / 10);
            else
                std::cout << "  ";
        }
        std::cout << "\n  ";
        for (int i = 0; i < BOARD_SIZE; ++i)
        {
            std::cout << std::format("{:2d}", i % 10);
        }
        std::cout << std::endl;
        for (pos_t i = 0; i < BOARD_SIZE; ++i)
        {
            std::cout << std::format("{:<3d}", i);
            for (pos_t j = 0; j < BOARD_SIZE; ++j)
            {
                auto color = Color::None;
                if (board.Get({i, j}, Color::White))
                    color = Color::White;
                if (board.Get({i, j}, Color::Black))
                    color = Color::Black;
                auto isFromPrev = prevMove.GetFirst() == StonePos{i, j} || prevMove.GetSecond() == StonePos{i, j};
                WritePiece(color, isFromPrev);
            }
            std::cout << std::endl;
        }

        WriteMove(prevMove);
    }
    if (board.GetResult() != Color::None)
    {
        std::cout << WriteColor(board.GetResult()) << " wins\n";
    }
}

void FileLogger::WriteInfo(const std::string &prefix, const std::string &info)
{
    if (!prefix.empty())
        std::cout << "[" << prefix << "] ";
    std::cout << info << std::endl;
}
