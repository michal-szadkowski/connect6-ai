#ifndef CONNECT6_AI_REPLAYMEMORY_H
#define CONNECT6_AI_REPLAYMEMORY_H

#include "../Game/Board.h"


struct Experience {
    Board start;
    StonePos action;
    double reward = 0;
    Board result;
    Experience() = default;
    Experience(const Board &start, StonePos &action, double reward, const Board &result)
            : start(start), action(action), reward(reward), result(result) {};
};

class ReplayMemory {
private:
    std::vector<Experience> experiences;
    int maxSize;
public:
    ReplayMemory(int maxSize) : maxSize(maxSize) {}
    std::vector<Experience> GetRandomSample(int sampleSize);
    void AddExperience(Experience exp);
};


#endif //CONNECT6_AI_REPLAYMEMORY_H
