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
public:
    Agent(int memSize, double eps = 0) : memory(memSize) { net = NNet(); }
    StonePos GetMove(const Board &board);
    double Train(int batches);

    void Save(std::string path);
    void Load(std::string path);
    static torch::Tensor Board2Tensor(const Board &boards);
    void SetEps(double eps) { this->eps = eps > 0.05 ? eps : 0.05; }
    void AddExperience(const Experience &experience);
};


#endif //CONNECT6_AI_AGENT_H
