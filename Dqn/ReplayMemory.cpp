#include "ReplayMemory.h"
#include <algorithm>
#include <stdexcept>
#include "../Random.h"


std::vector<Experience> ReplayMemory::GetRandomSample(int sampleSize)
{
    std::vector<Experience> result;
    result.reserve(sampleSize);
    if (sampleSize == 0)
        return result;
    if (sampleSize > experiences.size())
        throw std::logic_error("not enough experiences to sample from");
    std::ranges::sample(experiences, std::back_insert_iterator(result), sampleSize, Random::GetGen());
    for (int i = 0; i < sampleSize; i++)
    {
        result[i] = Randomize(result[i]);
    }
    return result;
}

void ReplayMemory::AddExperience(const Experience &exp)
{
    if (maxSize == 0)
        return;
    std::lock_guard<std::mutex> lock{expmutex};
    if (experiences.size() >= maxSize)
    {
        auto delPos = Random::RandomInRange(0, experiences.size());
        experiences[delPos] = exp;
        experiences[delPos].idx = delPos;
    }
    else
    {
        experiences.push_back(exp);
        experiences[experiences.size() - 1].idx = experiences.size() - 1;
    }
}

void ReplayMemory::Rotate(torch::Tensor &t) { t = t.rot90(1, {1, 2}); }

void ReplayMemory::Rotate(std::pair<int, int> &p)
{
    const auto tmp = p.second;
    p.second = p.first;
    p.first = 18 - tmp;
}

void ReplayMemory::Flip(torch::Tensor &t) { t = t.flip({1}); }
void ReplayMemory::Flip(std::pair<int, int> &p) { p.first = 18 - p.first; }

Experience ReplayMemory::Randomize(const Experience &exp)
{
    auto s = exp.start;
    auto a = exp.action;
    auto r = exp.result;
    int rot = Random::RandomInRange(0, 4);

    for (int i = 0; i < rot; i++)
    {
        Rotate(s);
        Rotate(a);
        Rotate(r);
    }
    return {s, a, exp.reward, exp.neg, r};
}
