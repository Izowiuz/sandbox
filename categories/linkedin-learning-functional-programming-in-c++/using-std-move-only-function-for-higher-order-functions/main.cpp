#include <cstdlib>
#include <functional>

#include "spdlog/spdlog.h"

void apply_function(std::move_only_function<int(int)> func, int value)
{
    const auto result = func(value);
    spdlog::info("func result: {}", result);
}

/**
 * Params&&... params -> perfect forwarding parametrów do wywołania func()
 */
template <typename Return, typename... Params>
Return apply_function_templated(std::move_only_function<Return(Params...)> func, Params&&... params)
{
    return func(std::forward<Params>(params)...);
}

int main()
{
    {
        auto lambda_square = [](int x) { return x * x; };
        apply_function(std::move(lambda_square), 5);
    }

    {
        std::move_only_function<int(int)> square = [](int x) { return x * x; };
        spdlog::info("square: {}", apply_function_templated(std::move(square), 5));

        std::move_only_function<int(int, int, int)> add_three = [](int x, int y, int z) { return x + y + z; };
        spdlog::info("add_three: {}", apply_function_templated(std::move(add_three), 1, 2, 3));

        std::move_only_function<int(int, int)> add_three_v2 = [y = 4](int x, int z) { return x + y + z; };
        spdlog::info("add_three_v2: {}", apply_function_templated(std::move(add_three_v2), 1, 3));
    }

    return EXIT_SUCCESS;
}
