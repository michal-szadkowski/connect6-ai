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
    std::ranges::sample(experiences, std::back_insert_iterator(result), sampleSize,
                        Random::getGen());
    for (int i = 0; i < sampleSize; i++) {
        result[i] = Randomize(result[i]);
    }
    return result;
}
void ReplayMemory::AddExperience(const Experience &exp) {
    while (experiences.size() >= maxSize) {
        auto delPos = Random::RandomInRange(0, experiences.size());
        experiences.erase(experiences.begin() + delPos);
    }
    experiences.push_back(exp);
}

void ReplayMemory::Rotate(torch::Tensor &t) {
    t = t.rot90(1, {1, 2});
}
void ReplayMemory::Rotate(std::pair<int, int> &p) {
    const auto tmp = p.second;
    p.second = p.first;
    p.first = 18 - tmp;
}
void ReplayMemory::Flip(torch::Tensor &t) {
    t = t.flip({1});
}
void ReplayMemory::Flip(std::pair<int, int> &p) {
    p.first = 18 - p.first;
}
Experience ReplayMemory::Randomize(const Experience &exp) {
    auto s = exp.start;
    auto a = exp.action;
    auto r = exp.result;
    int rot = Random::RandomInRange(0, 3);;
    for (int i = 0; i < rot; i++) {
        Rotate(s);
        Rotate(a);
        Rotate(r);
    }
    if (Random::RandomInRange(0, 1)) {
        Flip(s);
        Flip(a);
        Flip(r);
    }
    // rot = Random::RandomInRange(0, 3);
    // for (int i = 0; i < rot; i++) {
    //
    // }
    // if (Random::RandomInRange(0, 1)) {
    // }

    return {s, a, exp.reward, exp.switchTurns, r};
}
