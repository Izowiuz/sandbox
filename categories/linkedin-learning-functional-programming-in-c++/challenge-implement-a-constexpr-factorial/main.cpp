#include <array>
#include <cstdlib>

#include "spdlog/spdlog.h"

constexpr int factorial(int n)
{
    if (n <= 1) {
        return 1;
    }

    int ret{ 1 };

    for (int i = 1; i <= n; ++i) {
        ret *= i;
    }

    return ret;
}

int main()
{
    constexpr int f5 = factorial(5);

    spdlog::info("constexpr int f5: {}", f5);

    for (int i = 0; i <= 10; ++i) {
        spdlog::info("n: {}, factorial(n): {}", i, factorial(i));
    }

    std::array<int, factorial(4)> arr;
    spdlog::info("size of array<int, factorial(4)>: {}", arr.size());

    return EXIT_SUCCESS;
}
