#include "Game.h"

Game::Game(Player &black, Player &white) : black(black), white(white) {
    board = Board();
    black.SetColor(Black);
    white.SetColor(White);
}

Color Game::Play() {
    return White;
}
