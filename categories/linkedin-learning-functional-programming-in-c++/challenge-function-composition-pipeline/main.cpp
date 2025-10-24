#include <cstdlib>

#include <spdlog/spdlog.h>

auto compose(auto f1, auto f2, auto f3)
{
    return [f1, f2, f3](int x) { return f1(f2(f3(x))); };
}

int main()
{
    auto decrement = [](int x) { return x - 1; };
    auto double_value = [](int x) { return x * 2; };
    auto add_3 = [](int x) { return x + 3; };
    auto pipeline = compose(decrement, double_value, add_3);

    spdlog::info("pipeline result for 5: {}", pipeline(5));

    return EXIT_SUCCESS;
}
