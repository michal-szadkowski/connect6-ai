#include <iostream>
#include <format>
#include "ConsoleLogger.h"

#define RESET   "\033[0m"
#define WHITE   "\033[37m"
#define BOLDWHITE   "\033[1m\033[39m"

void ConsoleLogger::WriteMove(const Move& move)
{
    if (move.GetFirst() != StonePos::Empty())
        std::cout << std::format("[{:d} {:d}]", move.GetFirst().GetX(), move.GetFirst().GetY());
    if (move.GetSecond() != StonePos::Empty())
        std::cout << std::format(" [{:d} {:d}]", move.GetSecond().GetX(), move.GetSecond().GetY());
}

void ConsoleLogger::WriteBoard(const Board& board, const Move& prevMove)
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
        for (int i = 0; i < BOARD_SIZE; ++i) { std::cout << std::format("{:2d}", i % 10); }
        std::cout << std::endl;
        for (pos_t i = 0; i < BOARD_SIZE; ++i)
        {
            std::cout << std::format("{:<3d}", i);
            for (pos_t j = 0; j < BOARD_SIZE; ++j)
            {
                bool w = board.Get({i, j}, Color::White);
                bool b = board.Get({i, j}, Color::Black);
                std::string s = w ? "X" : b ? "O" : WHITE ".";
                if (prevMove.GetFirst() == StonePos{i, j} || prevMove.GetSecond() == StonePos{i, j})
                    std::cout << BOLDWHITE;
                std::cout << s << RESET << " ";
            }
            std::cout << std::endl;
        }

        WriteMove(prevMove);
    }
    if (board.GetResult() != Color::None) { std::cout << WriteColor(board.GetResult()) << " wins"; }
}

void ConsoleLogger::WriteInfo(const std::string& prefix, const std::string& info)
{
    if (!prefix.empty())
        std::cout << "[" << prefix << "] ";
    std::cout << info << std::endl;
}
