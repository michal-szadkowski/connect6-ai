#include <iostream>
#include <format>
#include "HumanPlayer.h"

void PrintBoardH(const Board &brd) {
    std::cout << "  ";
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (i >= 10)
            std::cout << std::format("{:2d}", i / 10);
        else std::cout << "  ";
    }
    std::cout << "\n  ";
    for (int i = 0; i < BOARD_SIZE; ++i) {
        std::cout << std::format("{:2d}", i % 10);
    }
    std::cout << std::endl;
    for (char i = 0; i < BOARD_SIZE; ++i) {
        std::cout << std::format("{:<3d}", i);
        for (char j = 0; j < BOARD_SIZE; ++j) {
            bool w = brd.Get({i, j}, Color::White);
            bool b = brd.Get({i, j}, Color::Black);
            char s = w ? 'X' : b ? 'O' : '.';
            std::cout << std::format("{:2}", s);
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
Move HumanPlayer::GetMove(const Board &board, const Move &prevMove) {
    int x1 = -1, y1 = -1;
    int x2 = -1, y2 = -1;
    PrintBoardH(board);
    std::string col = this->GetColor() == Color::Black ? "black" : "white";
    std::cout << col << " pos:\nfirst:\n";
    std::cin >> x1 >> y1;
    if (board.ExpectingFullMove()) {
        std::cout << "second: \n";
        std::cin >> x2 >> y2;
        return {{static_cast<char>(x1),
                 static_cast<char>(y1)},
                {static_cast<char>(x2),
                 static_cast<char>(y2)},
                this->GetColor()};
    }
    return {{static_cast<char>(x1),
             static_cast<char>(y1)},
            this->GetColor()};

}
