#include <iostream>
#include <memory>
#include "Game/Game.h"
#include "Players/HumanPlayer.h"
#include "Players/RandomPlayer.h"
#include "Mcts/Node.h"
#include "Mcts/Tree.h"

int main() {
//    RandomPlayer p1{};
//    RandomPlayer p2{};
//    Game game = Game(p1, p2);
//    game.Play();
    Board br;
    auto n1 = std::make_shared<Node>(std::weak_ptr<Node>(), StonePos{14, 14}, Color::Black, false);
    auto b = n1->GetResultingBoard(br);
    auto c = n1->Expand(b);
    b = c[0]->GetResultingBoard(br);
    c[0]->Expand(b);

    Tree t(br);
    t.Select()->Expand(br);
    t.Select()->Expand(br);
    return 0;
}
