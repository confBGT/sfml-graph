#pragma once

#include <vector>

class Random {
public:
    Random(std::size_t size);
public:
    int next();
private:
    std::size_t size;
    std::size_t count;
    std::vector<int> vec;
};
