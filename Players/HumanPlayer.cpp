#include <iostream>
#include "HumanPlayer.h"

Move HumanPlayer::GetMove(const Board &board, const Move &prevMove) {
    int x1, y1;
    int x2 = -1, y2 = -1;
    std::string col = this->GetColor() == Color::Black ? "black" : "white";
    std::cout << col << " pos:\nfirst:\n";
    std::cin >> x1 >> y1;
    if (board.StonesPlacedCount() > 0) {
        std::cout << "second: \n";
        std::cin >> x2 >> y2;
    }
    return {{static_cast<char>(x1),
             static_cast<char>(y1)},
            {static_cast<char>(x2),
             static_cast<char>(y2)},
            this->GetColor()};
}
