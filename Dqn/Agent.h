#ifndef CONNECT6_AI_AGENT_H
#define CONNECT6_AI_AGENT_H


#include <memory>
#include "Network.h"
#include "ReplayMemory.h"

/**
 * Represents agent in RL environment, makes decitions and remebers them in memory
 */
class Agent
{
private:
    std::shared_ptr<ReplayMemory> memory;

    NNet net;
    torch::Device device{torch::kCPU};
    std::shared_ptr<torch::optim::Optimizer> optimizer;

    /**
     * Converts board to 3D tensor where 1st dim is channel
     */
    static torch::Tensor Board2Tensor(const Board &board);

    /**
     * Clones model
     * @param model Model to clone to
     * @param target_model Model to clone from
     */
    void CloneModel(torch::nn::Module &model, const torch::nn::Module &target_model);

public:
    /**
     * Creates new agent with random network and RMSProp optimizer
     */
    Agent(int memSize)
    {
        memory = std::make_shared<ReplayMemory>(memSize);
        net = NNet();
        net->to(device);
        optimizer = std::make_shared<torch::optim::RMSprop>(net->parameters(), torch::optim::RMSpropOptions(0.001).weight_decay(1e-6));
    }

    /**
     * Creates new agent with the same memory and cloned network
     * @param agent Agent to copy from
     */
    Agent(const Agent &agent);

    /**
     * Sets device and sends network to it
     */
    void ToDevice(torch::Device device);

    /**
     * Evaluates the bord and selects the single stone position from it
     * @param board Board to select move on
     * @param stochastic If true the move selection will be probabilistic, else it will be the best
     * @return Selected move and its evaluation
     */
    std::pair<StonePos, double> GetMove(const Board &board, bool stochastic = false);

    /**
     * Performs training loop with experiences from memory, creates target network one per whole loop
     * @param batches How many times the loop should be performed
     * @return Average MSE over all batches
     */
    double Train(int batches);


    /**
     * Saves current network to file
     */
    void Save(const std::string &path);

    /**
     * Loads network from file
     */
    void Load(const std::string &path);


    /**
     * Adds experience
     * @param start Statring board
     * @param pos Action taken in board
     * @param result Resulting board
     */
    void AddExperience(const Board &start, const StonePos &pos, const Board &result);
};


#endif // CONNECT6_AI_AGENT_H
