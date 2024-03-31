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
#include "Arguments/ArgumentParser.h"
//#include <torch/torch.h>

int main(int argc, const char *argv[]) {

    ArgumentParser args(argc, argv);

    ConsoleLogger cl;
    RandomPlayer p1(cl);
    MctsPlayer p2(cl, 250000, 5);
    Game game = Game(p2, p1, cl);
    auto result = game.Play();

    return 0;
}
