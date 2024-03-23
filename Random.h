#ifndef CONNECT6_AI_RANDOM_H
#define CONNECT6_AI_RANDOM_H


#include <random>

class Random {
    static inline std::mt19937 gen{std::random_device{}()};
public:
    static void Seed(int seed);

    static int RandomInRange(int min, int max);
    static std::mt19937 getGen() { return gen; }
    template<typename T>
    static T SelectRandomElement(std::vector<T> vector) { return vector.at(RandomInRange(0, vector.size())); }
};


#endif //CONNECT6_AI_RANDOM_H
