#ifndef CONNECT6_AI_AGENT_H
#define CONNECT6_AI_AGENT_H


#include <memory>
#include "ReplayMemory.h"
#include "Network.h"

class Agent
{
private:
    std::shared_ptr<ReplayMemory> memory;

    NNet net;
    torch::Device device{torch::kCPU};
    std::shared_ptr<torch::optim::Optimizer> optimizer;

    static torch::Tensor Board2Tensor(const Board& boards);
    void CloneModel(torch::nn::Module& model, const torch::nn::Module& target_model);

public:
    Agent(int memSize)
    {
        memory = std::make_shared<ReplayMemory>(memSize);
        net = NNet();
        net->to(device);
        optimizer = std::make_shared<torch::optim::RMSprop>(net->parameters(), torch::optim::RMSpropOptions(0.001).weight_decay(1e-6));
    }

    Agent(const Agent& agent);

    void ToDevice(torch::Device device);

    std::pair<StonePos, double> GetMove(const Board& board, bool stochastic = false);
    double Train(int batches);

    void Save(const std::string& path);
    void Load(const std::string& path);

    void AddExperience(const Board& start, const StonePos& pos, const Board& result);
};


#endif //CONNECT6_AI_AGENT_H
