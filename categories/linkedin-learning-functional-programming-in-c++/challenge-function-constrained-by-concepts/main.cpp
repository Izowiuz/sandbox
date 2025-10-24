#include <concepts>
#include <cstdlib>

#include <spdlog/spdlog.h>

template <typename T>
concept IsFloatingPoint = std::is_floating_point_v<T>;

template <IsFloatingPoint T>
T multiply(T a, T b)
{
    return a * b;
}

int main()
{
    spdlog::info(multiply(1.3f, 2.6f));
    // does not compile
    // spdlog::info(multiply(1, 2));

    return EXIT_SUCCESS;
}
