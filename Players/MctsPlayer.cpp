#include "MctsPlayer.h"
#include "../Game/Game.h"
#include "RandomPlayer.h"
#include <chrono>
#include <random>
#include <iostream>

MctsPlayer::MctsPlayer() {
    tree = std::make_unique<Tree>();

}

Move MctsPlayer::GetMove(const Board &board, const Move &prevMove) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000; ++i) {
        auto leaf = tree->Select();
        auto toSimulate = tree->Expand(leaf);
        allNodes += toSimulate.size();
        if (toSimulate.empty())toSimulate.emplace_back(leaf);
        auto simulated = SelectRandom(toSimulate);
        auto win = SimulateGame(tree->GetBoardForNode(simulated));
        simulated->Propagate(win);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Time taken by function: "
              << duration.count() << " microseconds\n";
    std::cout << allNodes;
    return Move(StonePos(), Color::Black);
}

int MctsPlayer::RandomInRange(int min, int max) {
    static std::random_device randomDevice;
    static std::mt19937 mt(randomDevice());
    std::uniform_int_distribution<int> d(min, max - 1);
    return d(mt);
}

Color MctsPlayer::SimulateGame(const Board &board) {
    RandomPlayer p1;
    RandomPlayer p2;
    return Game(p1, p2, board).Play();
}

template<typename T>
T MctsPlayer::SelectRandom(std::vector<T> vector) {
    return vector.at(RandomInRange(0, vector.size()));
}
