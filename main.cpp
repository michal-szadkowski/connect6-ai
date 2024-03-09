#include <iostream>
#include "Game/Game.h"
#include "Players/HumanPlayer.h"
#include "Players/RandomPlayer.h"

int main() {
    HumanPlayer p1{};
    RandomPlayer p2{};
    Game game = Game(p1, p2);
    game.Play();
    return 0;
}
