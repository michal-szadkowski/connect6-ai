#ifndef CONNECT6_AI_AGENT_H
#define CONNECT6_AI_AGENT_H


#include <memory>
#include "Network.h"
#include "ReplayMemory.h"

class Agent
{
private:
    NNet net;
    torch::Device device{torch::kCPU};
    std::shared_ptr<torch::optim::Optimizer> optimizer;

    static torch::Tensor Board2Tensor(const Board& board);

    static void CloneModel(torch::nn::Module& model, const torch::nn::Module& target_model);

    torch::Tensor EvaluateBoard(torch::Tensor board, bool minimize);

public:
    std::shared_ptr<ReplayMemory> memory;

    Agent(int memSize)
    {
        memory = std::make_shared<ReplayMemory>(memSize);
        net = NNet();
        net->to(device);
        optimizer = std::make_shared<torch::optim::RMSprop>(net->parameters(), torch::optim::RMSpropOptions(2e-6).weight_decay(1e-5));
    }

    Agent(const Agent& agent);

    void ToDevice(torch::Device device);

    std::pair<StonePos, double> GetMove(const Board& board, double eps = 0);

    torch::Tensor GetTaken(const torch::Tensor& input);

    double Train(int batches);

    void AddExperience(const Board& start, const StonePos& pos, const Board& result);


    void Save(const std::string& path);

    void Load(const std::string& path);
};


#endif // CONNECT6_AI_AGENT_H
