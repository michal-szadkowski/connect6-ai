#include <iostream>
#include "HumanPlayer.h"

Move HumanPlayer::GetMove() {
    int x1, y1;
    int x2, y2;
    std::cout << "pos:\n";
    std::cin >> x1 >> y1;
    std::cin >> x2 >> y2;
    return Move(0, 0, this->GetColor());
}
