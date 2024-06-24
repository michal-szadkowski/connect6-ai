#ifndef CONNECT6_AI_REPLAYMEMORY_H
#define CONNECT6_AI_REPLAYMEMORY_H

#include <random>
#include <torch/torch.h>
#include "../Game/Board.h"

#include <utility>


struct Experience
{
    torch::Tensor start;
    std::pair<int, int> action;
    double reward = 0;
    bool neg = false;
    bool final = false;
    torch::Tensor result;

    Experience() = default;

    Experience(torch::Tensor start, const std::pair<int, int>& action, double reward, bool neg, bool final, torch::Tensor result) :
        start(std::move(start)), action(action), reward(reward), neg(neg), final(final), result(std::move(result)) {}
};

class ReplayMemory
{
private:
    std::mutex expmutex;
    int maxSize;
    std::vector<Experience> experiences;
    int insertPos = 0;


    static Experience Randomize(const Experience& exp);
    Experience Invert(const Experience& exp);

public:
    static void Rotate(torch::Tensor& t);
    static void Rotate(std::pair<int, int>& p);
    static void Flip(torch::Tensor& t);
    static void Flip(std::pair<int, int>& p);

    ReplayMemory(int maxSize) : maxSize(maxSize) { experiences.reserve(maxSize); }
    std::vector<Experience> GetRandomSample(int sampleSize);
    void AddExperience(const Experience& exp);
};


#endif // CONNECT6_AI_REPLAYMEMORY_H
