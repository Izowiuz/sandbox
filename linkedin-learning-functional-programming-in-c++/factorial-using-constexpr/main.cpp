spdlog.h"

    // this can also be:
    // constexpr int factorial(int n)
    consteval int factorial(int n)
{
    int ret{ 1 };

    for (int i = 1; i <= n; ++i) {
        ret *= i;
    }

    return ret;
}

int main()
{
    // compiletime computation
    constexpr auto result = factorial(5);
    spdlog::info(result);

    std::array<int, factorial(4)> arr;
    spdlog::info(arr.size());

    return EXIT_SUCCESS;
}
