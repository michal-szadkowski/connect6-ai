#include "Agent.h"
#include <torch/torch.h>
#include "../Random.h"

std::ostream &prt(const torch::Tensor &foo)
{
    std::cout << foo << "\n";
    return std::cout;
}

void Agent::CloneModel(torch::nn::Module &model, const torch::nn::Module &target_model)
{
    torch::NoGradGuard noGradGuard;
    auto new_params = target_model.named_parameters();
    auto params = model.named_parameters(true);
    auto buffers = model.named_buffers(true);
    for (auto &val : new_params)
    {
        auto name = val.key();
        auto *t = params.find(name);
        if (t != nullptr)
        {
            // *t = val.value().clone();
            t->copy_(val.value());
        }
        else
        {
            t = buffers.find(name);
            if (t != nullptr)
            {
                // *t = val.value().clone();
                t->copy_(val.value());
            }
        }
    }
}


Agent::Agent(const Agent &agent) : memory(agent.memory), device(torch::Device(agent.device.type()))
{
    net = NNet();
    CloneModel(*net, *(agent.net));
    net->to(agent.device);
    optimizer = agent.optimizer;
}

void Agent::ToDevice(torch::Device device)
{
    this->device = device;
    this->net->to(device);
}

torch::Tensor Agent::EvaluateBoard(const Board &board)
{
    torch::Tensor q1;

    int rot = Random::RandomInRange(0, 8);

    auto t1 = Board2Tensor(board).unsqueeze(0).to(device, torch::kF32);
    t1 = t1.rot90(rot / 2, {2, 3});
    if (rot % 2)
        t1 = t1.flip({2});
    q1 = net->forward(t1);
    q1 = q1 + 1 - t1[0][0].abs() * 4;
    if (rot % 2)
        q1 = q1.flip({1});
    q1 = q1.rot90(4 - (rot / 2), {1, 2});

    return q1;
}

std::pair<StonePos, double> Agent::GetMove(const Board &board, double eps)
{
    StonePos pos;

    auto q = EvaluateBoard(board);
    auto r = torch::normal(0, eps * 0.1, {19, 19}).clamp(-1, 1).to(device);
    int posId;
    double c = 0;
    // if (eps > Random::RandomDouble())
    // {
    //     pos = Random::SelectRandomElement(board.GetAllEmpty());
    //     return {pos, 0};
    // }
    // if (stochastic)
    // {
    //     q1 = q1.squeeze(0).flatten();
    //     q1 = q1.clamp(0, 2);
    //     auto p = q1.cumsum(0);
    //     p = p / p.max();
    //     auto r = 1 - Random::RandomDouble();
    //     posId = searchsorted(p, r, false, true).item<int>();
    //     while (posId >= 19 * 19 || t1[0][0][posId / 19][posId % 19].item<int>() != 0)
    //     {
    //         posId++;
    //         posId = posId % (19 * 19);
    //     }
    //     c = q1[posId].item<double>();
    // }
    // else
    auto eval = q + r;

    posId = eval.argmax().item<int>();
    c = q[0][pos.GetX()][pos.GetY()].item<double>();
    pos = StonePos(posId / 19, posId % 19);
    return {pos, c};
}


double Agent::Train(int batches)
{
    memory->RebuildWeights();
    double lossTotal = 0;
    const int sampleSize = 256;
    NNet net2;
    net2->to(device);
    for (int i = 0; i < batches; ++i)
    {
        if (i % 250 == 0)
            CloneModel(*net2, *net);
        auto sample = memory->GetWeightedSample(sampleSize);
        optimizer->zero_grad();
        torch::Tensor start = torch::zeros({sampleSize, 2, 19, 19});
        torch::Tensor result = torch::zeros({sampleSize, 2, 19, 19});

        for (int j = 0; j < sampleSize; j++)
        {
            start[j] = sample[j].start;
            result[j] = sample[j].result;
        }

        start = start.to(device, torch::kF32);
        result = result.to(device, torch::kF32);

        auto q1 = net->forward(start);
        auto target = q1.clone();

        torch::Tensor q2;
        torch::Tensor q2p;

        {
            torch::NoGradGuard noGrad;
            q2 = net->forward(result);
            q2p = net2->forward(result);
        }

        for (int j = 0; j < sampleSize; j++)
        {
            double dif = 0;
            if (sample[j].reward != 0)
            {
                dif = (target[j][sample[j].action.first][sample[j].action.second] - sample[j].reward).item<double>();
                target[j][sample[j].action.first][sample[j].action.second] = sample[j].reward;
            }
            else
            {
                auto argmax = q2p[j].argmax();
                auto max = 0.99 * q2[j].take(argmax).item<double>();
                if (sample[j].switchTurns)
                    max = -max;
                dif = target[j][sample[j].action.first][sample[j].action.second].item<double>() - max;
                target[j][sample[j].action.first][sample[j].action.second] = max;
            }
            memory->UpdateWeight(sample[j].idx, dif * dif);
        }

        auto crit = torch::nn::MSELoss();
        auto loss = crit(q1, target);
        lossTotal += loss.item<double>();
        loss.backward();
        optimizer->step();
    }
    return lossTotal / batches;
}

torch::Tensor Agent::Board2Tensor(const Board &board)
{
    auto t = torch::zeros({2, BOARD_SIZE, BOARD_SIZE}, torch::kI8);
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
    t[1] =
        !board.ExpectingFullMove() ? torch::ones({BOARD_SIZE, BOARD_SIZE}, torch::kI8) : torch::zeros({BOARD_SIZE, BOARD_SIZE}, torch::kI8);

    return t;
}

void Agent::Save(const std::string &path) { torch::save(net, path); }

void Agent::Load(const std::string &path)
{
    torch::load(net, path);
    net->to(device);
}

void Agent::AddExperience(const Board &start, const StonePos &pos, const Board &result)
{
    memory->AddExperience({Agent::Board2Tensor(start),
                           {pos.GetX(), pos.GetY()},
                           result.GetResult() != Color::None ? 1.0 : 0,
                           result.GetTurn() != start.GetTurn(),
                           Agent::Board2Tensor(result)});
}
