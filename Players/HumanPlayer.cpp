#include <iostream>
#include "HumanPlayer.h"

Move HumanPlayer::GetMove() {
    int x1, y1;
    int x2, y2;
    std::string col = this->GetColor() == Black ? "black" : "white";
    std::cout << col << "pos:\n";
    std::cin >> x1 >> y1;
    std::cin >> x2 >> y2;
    return Move(x1, y1, x2, y2, this->GetColor());
}
