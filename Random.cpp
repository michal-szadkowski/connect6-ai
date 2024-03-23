#include "Random.h"


void Random::Seed(int seed) {
    gen = std::mt19937(seed);
}

int Random::RandomInRange(int min, int max) {
    std::uniform_int_distribution<int> d(min, max - 1);
    return d(gen);

}