#include <concepts>
#include <cstdlib>

#include "spdlog/spdlog.h"

template <typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template <Arithmetic T>
T sum(T a, T b)
{
    return a + b;
}

int main()
{
    spdlog::info(sum(1, 3));
    spdlog::info(sum(0.3f, 3.f));
    // does not compile
    // spdlog::info(sum("a", 3.f));

    return EXIT_SUCCESS;
}
