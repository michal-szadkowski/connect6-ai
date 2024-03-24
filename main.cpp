#include <iostream>
#include <memory>
#include "Game/Game.h"
#include "Players/HumanPlayer.h"
#include "Players/RandomPlayer.h"
#include "Mcts/Node.h"
#include "Mcts/Tree.h"
#include "Players/MctsPlayer.h"
#include "Random.h"
#include "Interface/ConsoleLogger.h"

int main() {
    ConsoleLogger cl;
//    Random::Seed(1);
//    RandomPlayer p1{};
//    RandomPlayer p2{};
//    Game game = Game(p1, p2);
//    auto result = game.Play();
//    if (result == Color::Black) std::cout << "black\n";
//    else if (result == Color::White) std::cout << "white\n";
//    else if (result == Color::Draw)std::cout << "draw\n";


    Board board;
    HumanPlayer p1(cl);
    MctsPlayer p2(cl);
    Game game = Game(p2, p1);
    auto result = game.Play();
    cl.WriteInfo(cl.WriteColor(result));

    return 0;
}
