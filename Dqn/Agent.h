#ifndef CONNECT6_AI_AGENT_H
#define CONNECT6_AI_AGENT_H


#include <memory>
#include "ReplayMemory.h"
#include "Network.h"

class Agent {
private:
    ReplayMemory memory;
    NNet net;
    double eps;

    std::unique_ptr<torch::optim::Optimizer> optimizer;

    static torch::Tensor Board2Tensor(const Board &boards);
    torch::Device &device;

public:
    Agent(int memSize, torch::Device &device, double eps = 0) : memory(memSize), device(device) {
        net = NNet();
        optimizer = std::make_unique<torch::optim::AdamW>(net->parameters(),
                                                          torch::optim::AdamWOptions(0.01).weight_decay(0.01).eps(0.1));
        net->to(device);
    }
    std::pair<StonePos, double> GetMove(const Board &board);
    double Train(int batches);

    void Save(const std::string &path);
    void Load(const std::string &path);
    void SetEps(double eps) { this->eps = eps >= 0 ? eps : 0; }
    void AddExperience(const Board &start, const StonePos &pos, const Board &result);
};


#endif //CONNECT6_AI_AGENT_H
