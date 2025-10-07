#include <array>
#include <cstdlib>

#include "spdlog/spdlog.h"

consteval int fibonacci(int n)
{
    if (n <= 1) {
        return n;
    }

    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main()
{
    constexpr auto fib7 = fibonacci(7);
    spdlog::info(fib7);

    constexpr auto fib10 = fibonacci(10);
    spdlog::info(fib10);

    std::array<int, fibonacci(10)> arr;
    spdlog::info(arr.size());

    return EXIT_SUCCESS;
}
