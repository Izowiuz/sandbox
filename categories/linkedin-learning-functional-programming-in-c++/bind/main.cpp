#include <cstdlib>
#include <functional>

#include <spdlog/spdlog.h>

int sum(int x, int y)
{
    return x + y;
}

int main()
{
    // std::bind
    auto add_ten = std::bind(&sum, 10, std::placeholders::_1);

    spdlog::info("add ten to 4: {}", add_ten(4));
    spdlog::info("add ten to 10: {}", add_ten(10));
    spdlog::info("add ten to 0: {}", add_ten(0));

    // lambda alternative
    auto add_ten_lambda = [](int param) { return sum(10, param); };

    spdlog::info("add ten to 4 lambda: {}", add_ten_lambda(4));
    spdlog::info("add ten to 10 lambda: {}", add_ten_lambda(10));
    spdlog::info("add ten to 0 lambda: {}", add_ten_lambda(0));

    return EXIT_SUCCESS;
}
