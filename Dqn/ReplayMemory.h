#ifndef CONNECT6_AI_REPLAYMEMORY_H
#define CONNECT6_AI_REPLAYMEMORY_H

#include <torch/torch.h>
#include "../Game/Board.h"

#include <utility>


/**
 * Represents position from game, action taken in that position and resulting position with reward if resulting position is winning
 */
struct Experience
{
    torch::Tensor start;
    std::pair<int, int> action;
    double reward = 0;
    bool switchTurns = false;
    torch::Tensor result;

    Experience(torch::Tensor start, const std::pair<int, int> &action, double reward, bool switchTurns, torch::Tensor result) :
        start(start.clone()), action(action), reward(reward), switchTurns(switchTurns), result(result.clone())
    {}
};

/**
 * Container for experiences
 */
class ReplayMemory
{
private:
    std::vector<Experience> experiences;
    std::mutex expmutex;
    int maxSize;

    /**
     * Rotates tensor right by 90 deg
     */
    static void Rotate(torch::Tensor &t);

    /**
     * Rotates coorditanes right by 90 deg
     */
    static void Rotate(std::pair<int, int> &p);

    /**
     * Mirrors tensor up/down
     */
    static void Flip(torch::Tensor &t);

    /**
     * Mirrors coordinates up/down
     */
    static void Flip(std::pair<int, int> &p);

    /**
     * Randomly flips and rotates experience
     */
    static Experience Randomize(const Experience &exp);

public:
    /**
     * Creates container which can hold maxSize memories
     */
    ReplayMemory(int maxSize) : maxSize(maxSize) {}

    /**
     * @param sampleSize Size of vector to return
     * @return Vector of randomly selected and randomly fliped and mirrored experiences from memory
     */
    std::vector<Experience> GetRandomSample(int sampleSize);

    /**
     * Adds experience, if memory is full randomly deletes one and replaces with new one
     * @param exp Experience to add
     */
    void AddExperience(const Experience &exp);
};


#endif // CONNECT6_AI_REPLAYMEMORY_H
