#include <cstdlib>
#include <ranges>

#include "fmt/ranges.h"
#include "spdlog/spdlog.h"

int main()
{
    // auto const vec = std::ranges::views::iota(1, 101) | std::ranges::to<std::vector>();
    auto pipeline = std::ranges::views::iota(1, 101) |
                    std::ranges::views::transform([](int element) { return element * element; }) |
                    std::ranges::views::filter([](int element) { return element % 5 == 0; }) |
                    std::ranges::views::take(10);

    for (const auto& element : pipeline) {
        spdlog::info("element: {}", element);
    }

    return EXIT_SUCCESS;
}
