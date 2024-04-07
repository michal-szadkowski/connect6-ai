#include "Agent.h"
#include "../Random.h"
#include <torch/torch.h>

std::ostream &prt(const torch::Tensor &foo) {
    std::cout << foo << "\n";
    return std::cout;
}

StonePos Agent::GetMove(const Board &board) {
    StonePos pos;
    if (Random::RandomDoble() < 0.1) {
        pos = Random::SelectRandomElement(board.GetAllEmpty());
    } else {
        auto t1 = Board2Tensor(board);
        auto q1 = net->forward(t1);
        q1 = q1 - 2 * t1[0].abs();
        int max = q1.argmax().item<int>();
        pos = StonePos(max / 19, max % 19);
    }
    return pos;
}
double Agent::Train(int batches) {
    double lossTotal = 0;
    torch::optim::SGD optimizer(net->parameters(), 0.02);
    for (int i = 0; i < batches; ++i) {

        auto sample = memory.GetRandomSample(64);
        for (auto &s: sample) {
            optimizer.zero_grad();

            auto t1 = Board2Tensor(s.start);
            auto q1 = net->forward(t1);
            auto target = q1.clone();

            double r = s.reward;
            target[s.action.GetX()][s.action.GetY()] = r;
            if (s.result.GetResult() != Color::None) {
                torch::Tensor q2;
                auto t2 = Board2Tensor(s.result);
                {
                    torch::NoGradGuard noGrad;
                    q2 = net->forward(t2);
                }
                auto max = 0.996 * torch::max(q2);
                target[s.action.GetX()][s.action.GetY()] += max;
            }
            auto loss = torch::mse_loss(q1, target);
            lossTotal += loss.item<double>();
            loss.backward();
            optimizer.step();
        }
    }
    return lossTotal / batches;
}
torch::Tensor Agent::Board2Tensor(const Board &board) {
    auto t = torch::zeros({1, 19, 19});
    Color c = board.GetTurn();
    for (pos_t i = 0; i < BOARD_SIZE; ++i) {
        for (pos_t j = 0; j < BOARD_SIZE; ++j) {
            if (board.Get({i, j}, c))
                t[0][i][j] = 1;
            else if (board.Get({i, j}, Reverse(c)))
                t[0][i][j] = -1;
        }
    }
    return t;
}
void Agent::Save(std::string path) {
    net->pretty_print(std::cout);
    torch::save(net, path);
}
void Agent::Load(std::string path) {
    torch::load(net, path);
}
void Agent::AddExperience(const Experience &experience) {
    memory.AddExperience(experience);
}
