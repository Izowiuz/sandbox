#include <cstdlib>
#include <numeric>
#include <ranges>
#include <vector>

#include "boost/hana.hpp"
#include "fmt/ranges.h"
#include "spdlog/spdlog.h"

int main()
{
    auto const numbers = std::ranges::views::iota(1, 13) | std::ranges::to<std::vector>();
    auto even_numbers = numbers | std::ranges::views::filter([](auto const element) { return element % 2 != 0; });
    auto squared_even_numbers =
        even_numbers | std::ranges::views::transform([](auto const element) { return element * element; });
    auto const sum_of_squares =
        std::accumulate(squared_even_numbers.begin(), squared_even_numbers.end(), 0, [](auto sum, auto element) {
            return sum + element;
        });
    auto const result_tuple = boost::hana::make_tuple(sum_of_squares, sum_of_squares * 2);

    spdlog::info("sum_of_squares: {}, sum_of_squares * 2: {}",
                 boost::hana::at_c<0>(result_tuple),
                 boost::hana::at_c<1>(result_tuple));

    return EXIT_SUCCESS;
}
