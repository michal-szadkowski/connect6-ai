#include "MctsPlayer.h"
#include "../Game/Game.h"
#include "RandomPlayer.h"
#include <chrono>
#include <iostream>

MctsPlayer::MctsPlayer(Logger &logger) : logger(logger) {
    tree = std::make_unique<Tree>();
}

Move MctsPlayer::GetMove(const Board &board, const Move &prevMove) {
    PostMoveToTree(prevMove);
    logger.WriteBoard(board, prevMove);
    auto start = std::chrono::high_resolution_clock::now();
    RunTreeAlgorithm();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::milliseconds>(end - start);

    auto s = tree->GetBestSequence();

    logger.WriteInfo(std::format("Time taken by function: {} milliseconds\n", duration.count()));

    Move move{s.first->GetPosition(), StonePos::Empty(), this->GetColor()};
    if (s.second.get()) {
        logger.WriteInfo(std::format("{} {}\n", s.first->GetWinRate(), s.second->GetWinRate()));
        move = {s.first->GetPosition(), s.second->GetPosition(), this->GetColor()};
    }
    logger.WriteInfo(std::format("{}\n", s.first->GetWinRate()));
    PostMoveToTree(move);
    return move;
}

Color MctsPlayer::SimulateGame(const Board &board) {
    if (board.GetResult() != Color::None) return board.GetResult();
    RandomPlayer p1;
    RandomPlayer p2;
    return Game(p1, p2, board).Play();
}

void MctsPlayer::PostMoveToTree(const Move &move) {
    if (move.GetFirst() != StonePos::Empty())
        tree->PushMoveToTree(move.GetFirst(), move.GetColor());

    if (move.GetSecond() != StonePos::Empty())
        tree->PushMoveToTree(move.GetSecond(), move.GetColor());
}

void MctsPlayer::RunTreeAlgorithm() {
    for (int i = 0; i < expCount; ++i) {
        auto leaf = tree->SelectLeaf();
        auto toSimulate = tree->ExpandAndGetForSimulation(leaf);
        auto simBoard = tree->GetBoardForNode(toSimulate);
        for (int j = 0; j < simCount; ++j) {
            auto win = SimulateGame(simBoard);
            toSimulate->PropagateResult(win);
        }
    }
}

