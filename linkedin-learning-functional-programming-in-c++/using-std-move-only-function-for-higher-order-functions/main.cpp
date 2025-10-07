#include <cstdlib>
#include <functional>

#include "spdlog/spdlog.h"

void apply_function(std::move_only_function<int(int)> func, int value)
{
    const auto result = func(value);
    spdlog::info("func result: {}", result);
}

/**
 * Params&&... params -> perfect forwarding parametrów do wywołania func(_
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
        std::move_only_function<int(int)> lambda_square = [](int x) { return x * x; };
        spdlog::info("lambda_square: {}", apply_function_templated(std::move(lambda_square), 5));
    }

    return EXIT_SUCCESS;
}
