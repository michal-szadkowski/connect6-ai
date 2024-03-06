#include <iostream>
#include "HumanPlayer.h"

Move HumanPlayer::GetMove(Board &board) {
    int x1, y1;
    int x2, y2;
    std::string col = this->GetColor() == Black ? "black" : "white";
    std::cout << col << "pos:\n";
    std::cin >> x1 >> y1;
    std::cin >> x2 >> y2;
    return Move({static_cast<char>(x1),
                 static_cast<char>(y1)},
                {static_cast<char>(x2),
                 static_cast<char>(y2)},
                this->GetColor());
}
