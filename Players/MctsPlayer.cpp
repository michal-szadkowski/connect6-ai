#include "MctsPlayer.h"
#include "../Game/Game.h"
#include "../Random.h"
#include "RandomPlayer.h"
#include <chrono>
#include <iostream>

MctsPlayer::MctsPlayer() {
    tree = std::make_unique<Tree>();

}
void PrintBoard(const Board &brd) {
    std::cout << "  ";
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (i >= 10)
            std::cout << std::format("{:2d}", i / 10);
        else std::cout << "  ";
    }
    std::cout << "\n  ";
    for (int i = 0; i < BOARD_SIZE; ++i) {
        std::cout << std::format("{:2d}", i % 10);
    }
    std::cout << std::endl;
    for (char i = 0; i < BOARD_SIZE; ++i) {
        std::cout << std::format("{:<3d}", i);
        for (char j = 0; j < BOARD_SIZE; ++j) {
            bool w = brd.Get({i, j}, Color::White);
            bool b = brd.Get({i, j}, Color::Black);
            char s = w ? 'X' : b ? 'O' : '.';
            std::cout << std::format("{:2}", s);
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

Move MctsPlayer::GetMove(const Board &board, const Move &prevMove) {
    PostMoveToTree(board, prevMove);
    PrintBoard(board);
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < expCount; ++i) {
        auto leaf = tree->Select();
        auto toSimulate = tree->Expand(leaf);
        auto simBoard = tree->GetBoardForNode(toSimulate);
        for (int j = 0; j < simCount; ++j) {
            auto win = SimulateGame(simBoard);
            toSimulate->Propagate(win);
        }

    }
    auto s = tree->GetBestSequence();

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Time taken by function: "
              << duration.count() << " milliseconds\n";


    tree->PushMoveToTree(s.first->GetPosition(), this->GetColor());
    if (s.second.get()) {
        tree->PushMoveToTree(s.second->GetPosition(), this->GetColor());
        std::cout << std::format("{} {}\n", s.first->GetWinRate(), s.second->GetWinRate());
        return {s.first->GetPosition(), s.second->GetPosition(), this->GetColor()};
    }
    std::cout << std::format("{}\n", s.first->GetWinRate());
    return {s.first->GetPosition(), StonePos::Empty(), this->GetColor()};
}

Color MctsPlayer::SimulateGame(const Board &board) {
    if (board.GetResult() != Color::None) return board.GetResult();
    RandomPlayer p1;
    RandomPlayer p2;
    return Game(p1, p2, board).Play();
}

void MctsPlayer::PostMoveToTree(const Board &board, const Move &move) {
    if (move.GetFirst() != StonePos::Empty())
        tree->PushMoveToTree(move.GetFirst(), move.GetColor());

    if (move.GetSecond() != StonePos::Empty())
        tree->PushMoveToTree(move.GetSecond(), move.GetColor());
}

