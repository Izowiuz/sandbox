#include <cstdlib>
#include <functional>

#include "spdlog/spdlog.h"

auto compose(auto f, auto g)
{
    return [f, g](auto x) { return std::invoke(f, std::invoke(g, x)); };
}

auto compose_without_invoke(auto f, auto g)
{
    return [f, g](auto x) { f(g(x)); };
}

int increment(int x)
{
    return x + 1;
}

int main()
{
    auto square = [](int x) { return x * x; };
    auto increment_and_square = compose(square, increment);
    auto increment_and_square_without_invoke = compose(square, increment);

    spdlog::info("increment_and_square for 2: {}", increment_and_square(2));
    spdlog::info("increment_and_square_without_invoke for 2: {}", increment_and_square_without_invoke(2));

    return EXIT_SUCCESS;
}
