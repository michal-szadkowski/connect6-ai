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

    static torch::Tensor Board2Tensor(const Board &board);


public:
    static void CloneModel(torch::nn::Module &model, const torch::nn::Module &target_model);
    std::shared_ptr<ReplayMemory> memory;


    Agent(int memSize)
    {
        memory = std::make_shared<ReplayMemory>(memSize);

        net = NNet();
        net->to(device);
        optimizer = std::make_shared<torch::optim::RMSprop>(net->parameters(),
                                                            torch::optim::RMSpropOptions(0.005).weight_decay(0.001).momentum(0.9));
    }

    Agent(const Agent &agent);
    void ToDevice(torch::Device device);
    torch::Tensor EvaluateBoard(const Board &board);

    std::pair<StonePos, double> GetMove(const Board &board, double stochastic = 0);
    double Train(int batches);

    void Save(const std::string &path);
    void Load(const std::string &path);
    void AddExperience(const Board &start, const StonePos &pos, const Board &result);
};


#endif // CONNECT6_AI_AGENT_H
