#include "rustirator.h"

#include <vector>
#include <map>
#include <iostream>

auto process(std::vector<int> v) -> std::vector<float>
{
    return rustirator::into_iter(v).filter([](int x)
                                           { return x % 2 == 0; })
        .map([](int x)
             { return x * x / 2.0; })
        .collect();
}

int main()
{

    // using namespace rustirator;

    for (auto x : process({1, 2, 3, 4, 5}))
    {
        std::cout << x << "\n";
    }

    return 0;
}