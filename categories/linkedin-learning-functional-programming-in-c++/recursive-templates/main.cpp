#include <cstdlib>

#include <spdlog/spdlog.h>

template <int N>
struct Factorial {
    static constexpr int value = N * Factorial<N - 1>::value;
};

template <>
struct Factorial<0> {
    static constexpr int value = 1;
};

int main()
{
    spdlog::info(Factorial<4>::value);

    return EXIT_SUCCESS;
}
