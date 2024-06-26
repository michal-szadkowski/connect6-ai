#include "Agent.h"
#include <torch/torch.h>
#include "../Random.h"

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


Agent::Agent(const Agent& agent) : device(torch::Device(agent.device.type())), memory(agent.memory)
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

torch::Tensor Agent::EvaluateBoard(torch::Tensor board, bool minimize)
{
    torch::Tensor q1;
    q1 = net->forward(board);
    auto taken = GetTaken(board);
    if (minimize)
        q1 = -q1;

    q1 = q1 - taken * 100;
    return q1;
}

std::pair<StonePos, double> Agent::GetAction(const Board& board, double eps)
{
    torch::NoGradGuard noGrad;
    StonePos pos;
    double c = 0;

    if (Random::RandomDouble() < eps) { pos = Random::SelectRandomElement(board.GetAllEmpty()); }
    else
    {
        auto t1 = Board2Tensor(board).unsqueeze(0).to(device, torch::kF32);
        auto eval = EvaluateBoard(t1, false);
        int posId;
        posId = eval.argmax().item<int>();
        pos = StonePos(posId / BOARD_SIZE, posId % BOARD_SIZE);
        c = eval[0][pos.GetX()][pos.GetY()].item<double>();
    }

    return {pos, c};
}

torch::Tensor Agent::GetTaken(const torch::Tensor& input)
{
    auto i1 = input.index({at::indexing::Slice(0, at::indexing::None), at::indexing::Slice(0, 1)}).squeeze(1);
    auto i2 = input.index({at::indexing::Slice(0, at::indexing::None), at::indexing::Slice(1, 2)}).squeeze(1);
    return i1 + i2;
}

double Agent::Train(int batches)
{
    double lossTotal = 0;
    const int sampleSize = 10240;
    NNet net2;
    net2->to(device);
    for (int i = 0; i < batches; ++i)
    {
        if (i % 5 == 0)
            CloneModel(*net2, *net);
        auto sample = memory->GetRandomSample(sampleSize);
        optimizer->zero_grad();
        torch::Tensor start = torch::zeros({sampleSize, 3, BOARD_SIZE, BOARD_SIZE});
        torch::Tensor result = torch::zeros({sampleSize, 3, BOARD_SIZE, BOARD_SIZE});
        for (int j = 0; j < sampleSize; j++)
        {
            start[j] = sample[j].start;
            result[j] = sample[j].result;
        }

        start = start.to(device, torch::kF32);

        auto q1 = net->forward(start).flatten(1, 2);
        auto target = q1.clone();

        result = result.to(device, torch::kF32);

        torch::Tensor q2;
        torch::Tensor q2p;
        {
            torch::NoGradGuard noGrad;
            q2 = net->forward(result).flatten(1, 2);
            q2p = net2->forward(result).flatten(1, 2);
        }

        torch::Tensor actions = torch::zeros({sampleSize}, torch::kInt32);
        for (int j = 0; j < sampleSize; j++)
        {
            actions[j] = sample[j].action.first * BOARD_SIZE + sample[j].action.second;
            // if (sample[j].neg)
            //     q2p[j] = -q2p[j];
        }

        q2p = q2p - 100 * GetTaken(result).flatten(1, 2);


        auto argmax = q2p.argmax(1);
        auto maxval = q2.index({torch::arange(sampleSize), argmax}) * 1;

        for (int j = 0; j < sampleSize; j++)
        {
            if (sample[j].neg)
                maxval[j] = -maxval[j];
            if (sample[j].final)
                maxval[j] = sample[j].reward;
        }

        target.index_put_({torch::arange(sampleSize), actions}, maxval);


        auto crit = torch::nn::MSELoss();
        auto loss = crit(q1, target);
        loss.backward();
        optimizer->step();
        lossTotal += loss.item<double>();
    }
    return lossTotal / batches;
}

torch::Tensor Agent::Board2Tensor(const Board& board)
{
    auto t = torch::zeros({3, BOARD_SIZE, BOARD_SIZE}, torch::kI8);
    for (pos_t i = 0; i < BOARD_SIZE; ++i)
    {
        for (pos_t j = 0; j < BOARD_SIZE; ++j)
        {
            if (board.Get({i, j}, board.GetTurn()))
                t[0][i][j] = 1;
            else if (board.Get({i, j}, Reverse(board.GetTurn())))
                t[1][i][j] = 1;
        }
    }
    t[2] = board.ExpectingFullMove() ? torch::ones({BOARD_SIZE,BOARD_SIZE}) : -torch::ones({BOARD_SIZE,BOARD_SIZE});
    // t[0][INPUTSIZE - 1] = board.GetTurn() == Color::Black ? 1 : -1;

    return t;
}

void Agent::Save(const std::string& path) { torch::save(net, path); }

void Agent::Load(const std::string& path)
{
    torch::load(net, path);
    net->to(device);
}

void Agent::AddExperience(const Board& start, const StonePos& pos, const Board& result)
{
    double reward = 0;
    if (result.GetResult() == Color::Black || result.GetResult() == Color::White)
        reward = 1;

    memory->AddExperience({
        Agent::Board2Tensor(start), {pos.GetX(), pos.GetY()}, reward, result.GetTurn() != start.GetTurn(),
        result.GetResult() != Color::None, Agent::Board2Tensor(result)
    });
}
