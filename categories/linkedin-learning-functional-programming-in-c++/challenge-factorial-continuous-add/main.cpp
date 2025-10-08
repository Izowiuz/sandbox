#include <cstdlib>
#include <numeric>
#include <ranges>
#include <vector>

#include "spdlog/spdlog.h"

int factorial_recursive(int n)
{
    if (n == 0 || n == 1) {
        return 1;
    }

    return n * factorial_recursive(n - 1);
}

int factorial_nonrecursive(int n)
{
    int ret{ 1 };

    for (int i = 1; i <= n; ++i) {
        ret *= i;
    }

    return ret;
}

int factorial_challenge_recursive(std::vector<int> const& vec)
{
    auto factorials = vec | std::views::transform([](int elem) { return factorial_recursive(elem); });
    return std::accumulate(factorials.begin(), factorials.end(), 0, [](int sum, int elem) { return sum + elem; });
}

int factorial_challenge_nonrecursive(std::vector<int> const& vec)
{
    auto factorials = vec | std::views::transform([](int elem) { return factorial_nonrecursive(elem); });
    return std::accumulate(factorials.begin(), factorials.end(), 0, [](int sum, int elem) { return sum + elem; });
}

int main()
{
    // test only 4! -> 1*2*3*4 == 24
    spdlog::info(factorial_recursive(4));
    spdlog::info(factorial_nonrecursive(4));

    // 1 + 2 + 6 + 24 + 120 == 153
    std::vector<int> v1{ 1, 2, 3, 4, 5 };
    spdlog::info("factorial_challenge_recursive: {}", factorial_challenge_recursive(v1));
    spdlog::info("factorial_challenge_nonrecursive: {}", factorial_challenge_nonrecursive(v1));

    return EXIT_SUCCESS;
}
