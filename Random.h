#ifndef CONNECT6_AI_RANDOM_H
#define CONNECT6_AI_RANDOM_H

#include <random>

/**
 * Static class encapsulating random generator to make sure all functions share
 * single generator.
 */
class Random
{
    static inline std::mt19937 gen{std::random_device{}()};

public:
    /**
     * Sets seed, instead of random device, for random number generator.
     */
    static void Seed(int seed);

    /**
     * @return random int in range [min,max) .
     */
    static int RandomInRange(int min, int max);

    /**
     * @return random double in range [0,1).
     */
    static double RandomDouble();

    /**
     *
     * @return Generator to use in stl functions.
     */
    static std::mt19937 &GetGen() { return gen; }

    /**
     *
     * @return Random element selected from vector.
     */
    template <typename T>
    static T SelectRandomElement(std::vector<T> vector)
    {
        return vector.at(RandomInRange(0, vector.size()));
    }
};

#endif // CONNECT6_AI_RANDOM_H
