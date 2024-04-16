#include "Agent.h"
#include "../Random.h"
#include <torch/torch.h>

std::ostream& prt(const torch::Tensor& foo)
{
    std::cout << foo << "\n";
    return std::cout;
}

void Agent::CloneModel(torch::nn::Module& model, const torch::nn::Module& target_model)
{
    torch::NoGradGuard noGradGuard;
    auto new_params = target_model.named_parameters();
    auto params = model.named_parameters(true);
    auto buffers = model.named_buffers(true);
    for (auto& val : new_params)
    {
        auto name = val.key();
        auto* t = params.find(name);
        if (t != nullptr) { t->copy_(val.value()); }
        else
        {
            t = buffers.find(name);
            if (t != nullptr) { t->copy_(val.value()); }
        }
    }
}


Agent::Agent(const Agent& agent): memory(agent.memory)
{
    net = NNet();
    net->to(agent.device);
    CloneModel(*net, *(agent.net));
    device = agent.device;
    optimizer = agent.optimizer;
}

void Agent::ToDevice(torch::Device device)
{
    this->device = device;
    this->net->to(device);
}

std::pair<StonePos, double> Agent::GetMove(const Board& board)
{
    StonePos pos;

    auto t1 = Board2Tensor(board).unsqueeze(0).to(device);
    auto q1 = net->forward(t1);
    q1 = q1 - t1[0][0].abs() * 3;
    int max = q1.argmax().item<int>();
    pos = StonePos(max / 19, max % 19);
    auto c = q1[0][pos.GetX()][pos.GetY()].item<double>();


    return {pos, c};
}


double Agent::Train(int batches)
{
    double lossTotal = 0;
    const int sampleSize = 256;
    NNet net2;
    CloneModel(*net2, *net);
    net2->to(device);
    for (int i = 0; i < batches; ++i)
    {
        auto sample = memory->GetRandomSample(sampleSize);
        optimizer->zero_grad();
        net->zero_grad();
        torch::Tensor start = torch::zeros({sampleSize, 2, 19, 19});
        torch::Tensor result = torch::zeros({sampleSize, 2, 19, 19});

        for (int j = 0; j < sampleSize; j++)
        {
            start[j] = sample[j].start;
            result[j] = sample[j].result;
        }
        start = start.to(device);
        result = result.to(device);

        auto q1 = net->forward(start);
        auto target = q1.clone();

        torch::Tensor q2;
        {
            torch::NoGradGuard noGrad;
            q2 = net2->forward(result);
        }

        for (int j = 0; j < sampleSize; j++)
        {
            if (sample[j].reward != 0) { target[j][sample[j].action.first][sample[j].action.second] = sample[j].reward; }
            else
            {
                auto max = 0.99 * torch::max(q2[j]);
                if (sample[j].switchTurns)
                    max = -max;
                target[j][sample[j].action.first][sample[j].action.second] = max;
            }
        }

        auto crit = torch::nn::SmoothL1Loss();
        auto loss = crit(q1, target);
        lossTotal += loss.item<double>();
        loss.backward();
        optimizer->step();
    }
    return lossTotal / batches;
}

torch::Tensor Agent::Board2Tensor(const Board& board)
{
    auto t = torch::zeros({2, BOARD_SIZE, BOARD_SIZE});
    Color c = board.GetTurn();
    for (pos_t i = 0; i < BOARD_SIZE; ++i)
    {
        for (pos_t j = 0; j < BOARD_SIZE; ++j)
        {
            if (board.Get({i, j}, c))
                t[0][i][j] = 1;
            else if (board.Get({i, j}, Reverse(c)))
                t[0][i][j] = -1;
        }
    }
    t[1] = !board.ExpectingFullMove() ? torch::ones({BOARD_SIZE,BOARD_SIZE}) : torch::zeros({BOARD_SIZE,BOARD_SIZE});

    return t;
}

void Agent::Save(const std::string& path) { torch::save(net, path); }

void Agent::Load(const std::string& path) { torch::load(net, path); }

void Agent::AddExperience(const Board& start, const StonePos& pos, const Board& result)
{
    memory->AddExperience({
        Agent::Board2Tensor(start), {pos.GetX(), pos.GetY()}, result.GetResult() != Color::None ? 1.0 : 0,
        result.GetTurn() != start.GetTurn(), Agent::Board2Tensor(result)
    });
}
