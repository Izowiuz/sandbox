#include <algorithm>
#include <cstdlib>
#include <numeric>
#include <ranges>
#include <string>
#include <vector>

#include "spdlog/spdlog.h"

int main()
{
    {
        // ranges equality

        std::string const a{ "lalala" };
        std::string const b{ "lala" };
        std::string const c{ "lalala" };

        // simple ranges operation
        bool equal{ false };

        equal = std::ranges::equal(a, b);
        spdlog::info("{}, {} equal? {}", a, b, equal);

        equal = std::ranges::equal(a, c);
        spdlog::info("{}, {} equal? {}", a, c, equal);
    }

    // cannot pass temporary - does not compile
    // std::ranges::begin(std::string{"lala"});

    {
        // composability
        std::vector<int> const v{ 1, 2, 3, 5, 7, 8 };

        auto is_odd = [](int const& element) { return element % 2 != 0; };
        auto results =
            v | std::views::filter(is_odd) | std::views::transform([](int const& element) { return element * 2; });

        spdlog::info("composability results:");
        for (auto const& r : results) {
            spdlog::info("{}", r);
        }
    }

    {
        // common_range and default_sentient interaction
        std::vector<int> const v{ 1, 2, 3, 5, 7, 8 };

        // this would not compile without the std::views::common part
        auto range = v | std::views::take_while([](int const& element) { return element < 5; }) | std::views::common;
        auto const result = std::accumulate(range.begin(), range.end(), 0);
        spdlog::info("accumulate result: {}", result);
    }

    {
        // sorting on a non trivial type
        struct Lala {
            std::string name;
            int index;
        };

        std::vector<Lala> v{ { .name = "a", .index = 4 }, { .name = "b", .index = 44 }, { .name = "c", .index = 1 } };

        auto print_vector = [](auto&& v) {
            for (auto const& element : v) {
                spdlog::info("{}, {}", element.index, element.name);
            }
        };

        spdlog::info("unsorted:");
        print_vector(v);

        std::ranges::sort(v, std::ranges::less(), &Lala::index);

        spdlog::info("sorted:");
        print_vector(v);
    }

    return EXIT_SUCCESS;
}
