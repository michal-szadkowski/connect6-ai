#include <iostream>
#include "Game/Game.h"
#include "Players/HumanPlayer.h"

int main() {
    HumanPlayer p1 = HumanPlayer();
    HumanPlayer p2 = HumanPlayer();
    Game game = Game(p1, p2);
    
    std::cout << "Hello, World!" << std::endl;
    return 0;
}