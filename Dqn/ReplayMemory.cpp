#include <algorithm>
#include "ReplayMemory.h"
#include "../Random.h"
#include <stdexcept>

std::vector<Experience> ReplayMemory::GetRandomSample(int sampleSize) {
    std::vector<Experience> result;
    if (sampleSize == 0)
        return result;
    if (experiences.empty())
        throw std::logic_error("no experiences to sample from");
    std::sample(experiences.begin(), experiences.end(), std::back_insert_iterator(result), sampleSize,
                Random::getGen());
    return result;
}
void ReplayMemory::AddExperience(Experience exp) {
    while (experiences.size() >= maxSize) {
        auto delPos = Random::RandomInRange(0, experiences.size());
        experiences.erase(experiences.begin() + delPos);
    }
    experiences.push_back(exp);
}