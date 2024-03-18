#include <iostream>
#include <memory>
#include "Game/Game.h"
#include "Players/HumanPlayer.h"
#include "Players/RandomPlayer.h"
#include "Mcts/Node.h"
#include "Mcts/Tree.h"
#include "Players/MctsPlayer.h"

int main() {
//    RandomPlayer p1{};
//    RandomPlayer p2{};
//    Game game = Game(p1, p2);
//    auto result = game.Play();
//    if (result == Color::Black) std::cout << "black";
//    else if (result == Color::White) std::cout << "white";
//    else if (result == Color::Draw)std::cout << "draw";
//    

    Board board;
    Move move = Move(StonePos::Empty(), StonePos::Empty(), Color::None);
    MctsPlayer player;
    player.SetColor(Color::Black);
    player.GetMove(board, move);

    return 0;
}
