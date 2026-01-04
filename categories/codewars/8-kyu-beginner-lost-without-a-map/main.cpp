#include <algorithm>
#include <cstdlib>
#include <fmt/ranges.h>
#include <spdlog/spdlog.h>

/*
Given an array of integers, return a new array with each value doubled.

For example:

[1, 2, 3] --> [2, 4, 6]
*/

std::vector<int> maps(const std::vector<int>& values)
{
    std::vector<int> result;
    result.reserve(values.size());

    std::transform(values.begin(), values.end(), std::back_inserter(result), [](int value) {
        return value * 2;
    });

    return result;
}

int main()
{
    spdlog::info("maps: {}", maps({ 1, 2, 3 }));

    return EXIT_SUCCESS;
}
