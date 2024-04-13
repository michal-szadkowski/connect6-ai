#ifndef CONNECT6_AI_REPLAYMEMORY_H
#define CONNECT6_AI_REPLAYMEMORY_H

#include "../Game/Board.h"
#include <torch/torch.h>

#include <utility>

struct Experience {
    torch::Tensor start;
    std::pair<int, int> action;
    double reward = 0;
    bool switchTurns = false;
    torch::Tensor result;
    Experience(torch::Tensor start, const std::pair<int, int> &action, double reward, bool switchTurns,
               torch::Tensor result)
        : start(start.clone()), action(action), reward(reward), switchTurns(switchTurns), result(result.clone()) {
    }
};

class ReplayMemory {
private:
    std::vector<Experience> experiences;
    int maxSize;
    static void Rotate(torch::Tensor &t);
    static void Rotate(std::pair<int, int> &p);
    static void Flip(torch::Tensor &t);
    static void Flip(std::pair<int, int> &p);
    static Experience Randomize(const Experience &exp);

public:
    ReplayMemory(int maxSize) : maxSize(maxSize) {
    }
    std::vector<Experience> GetRandomSample(int sampleSize);
    void AddExperience(const Experience &exp);
};


#endif //CONNECT6_AI_REPLAYMEMORY_H
