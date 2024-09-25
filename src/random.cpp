#include <random>
#include <numeric>

#include "random.h"

Random::Random(std::size_t size)
    : size(size), count(size - 1), vec(size)
{
    std::iota(vec.begin(), vec.end(), 0);
}

int Random::next() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<> dist(0, count);

    int i = dist(g);

    std::swap(vec[i], vec[count]);

    count -= 1;

    return vec[count + 1];
}
