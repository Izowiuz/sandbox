#include <concepts>
#include <cstdlib>

#include "spdlog/spdlog.h"

template <typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template <typename T>
concept Addable = requires(T a, T b) {
    { a + b } -> std::convertible_to<T>;
};

template <Arithmetic T>
T sum(T a, T b)
    requires Addable<T>
{
    return a + b;
}

int main()
{
    spdlog::info(sum(1, 5));
    spdlog::info(sum(1.4, 5.0));
    // does not compile
    // spdlog::info(sum("a", "b"));
    return EXIT_SUCCESS;
}
