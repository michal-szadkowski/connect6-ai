#ifndef CONNECT6_AI_REPLAYMEMORY_H
#define CONNECT6_AI_REPLAYMEMORY_H

#include <random>
#include <torch/torch.h>
#include "../Game/Board.h"

#include <utility>


struct Experience
{
    int idx;
    torch::Tensor start;
    std::pair<int, int> action;
    double reward = 0;
    bool switchTurns = false;
    torch::Tensor result;

    Experience() = default;
    Experience(torch::Tensor start, const std::pair<int, int> &action, double reward, bool switchTurns, torch::Tensor result) :
        start(std::move(start)), action(action), reward(reward), switchTurns(switchTurns), result(std::move(result))
    {}
};

class ReplayMemory
{
private:
    std::mutex expmutex;
    int maxSize;
    std::vector<Experience> experiences;

    std::discrete_distribution<int> distr;
    std::vector<double> weights;

    static Experience Randomize(const Experience &exp);

public:
    static void Rotate(torch::Tensor &t);
    static void Rotate(std::pair<int, int> &p);
    static void Flip(torch::Tensor &t);
    static void Flip(std::pair<int, int> &p);

    ReplayMemory(int maxSize) : maxSize(maxSize) { experiences.reserve(maxSize); }
    std::vector<Experience> GetRandomSample(int sampleSize);
    std::vector<Experience> GetWeightedSample(int sampleSize);
    void RebuildWeights();
    void AddExperience(const Experience &exp);
    void UpdateWeight(int idx, double newWeight);
};


#endif // CONNECT6_AI_REPLAYMEMORY_H
