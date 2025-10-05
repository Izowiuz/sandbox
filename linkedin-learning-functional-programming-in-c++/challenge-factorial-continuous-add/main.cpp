#include <cstdlib>
#include <numeric>
#include <ranges>
#include <vector>

#include "spdlog/spdlog.h"

int factorial(int n)
{
    if (n == 0 || n == 1) {
        return 1;
    }

    return n * factorial(n - 1);
}

int factorial_challange(std::vector<int> const& vec)
{
    auto factorials = vec | std::views::transform([](int elem) { return factorial(elem); });
    return std::accumulate(factorials.begin(), factorials.end(), 0, [](int sum, int elem) { return sum + elem; });
}

int main()
{
    // test only 4! -> 1*2*3*4 == 24
    spdlog::info(factorial(4));

    // 1 + 2 + 6 + 24 + 120 == 153
    std::vector<int> v1{ 1, 2, 3, 4, 5 };
    spdlog::info("factorial_challange: {}", factorial_challange(v1));

    return EXIT_SUCCESS;
}
