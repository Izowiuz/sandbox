#include <cstdlib>
#include <ranges>
#include <vector>

#include "fmt/ranges.h"
#include "spdlog/spdlog.h"

int main()
{
    std::vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

    auto pipeline_1 = v | std::views::filter([](int element) {
                          spdlog::info("filtering: {} % 2 == 0 == {}", element, (element % 2 == 0));
                          return element % 2 == 0;
                      }) |
                      std::views::transform([](int element) {
                          spdlog::info("transforming: {} * {} == {}", element, element, element * element);
                          return element * element;
                      });

    auto pipeline_2 = v | std::views::transform([](int element) {
                          spdlog::info("transforming: {} * {} == {}", element, element, element * element);
                          return element * element;
                      }) |
                      std::views::filter([](int element) {
                          spdlog::info("filtering: {} % 2 == 0 == {}", element, (element % 2 == 0));
                          return element % 2 == 0;
                      });

    spdlog::info("pipeline_1 output: {}\n", pipeline_1);
    spdlog::info("pipeline_2 output: {}\n", pipeline_2);

    return EXIT_SUCCESS;
}
