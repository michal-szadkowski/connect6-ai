#include "ConsoleLogger.h"
#include <format>
#include <iostream>

#define RESET "\033[0m"
#define WHITE "\033[37m"
#define BOLDWHITE "\033[1m\033[39m"

void ConsoleLogger::WritePiece(Color piece, bool isFromPrevMove)
{
    std::string s = WHITE ".";
    if (piece == Color::White)
        s = isFromPrevMove ? BOLDWHITE : "" "X";
    if (piece == Color::Black)
        s = isFromPrevMove ? BOLDWHITE : "" "O";;
    std::cout << s << RESET << " ";
}
