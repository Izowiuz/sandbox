#include <cstdlib>
#include <iostream>
#include <numeric>
#include <ranges>
#include <vector>

#include <spdlog/spdlog.h>

template <typename Collection>
void print_collection(Collection const& collection)
{
    std::cout << "[ ";
    bool first = true;

    for (auto const& element : collection) {
        if (!first) {
            std::cout << ", ";
        }

        std::cout << element;
        first = false;
    }

    std::cout << " ]\n";
}

template <typename Range>
int accumulate_demo(Range const& collection)
{
    return std::accumulate(collection.begin(), collection.end(), 0, [](int sum, int x) { return sum + x; });
}

// we do not want to allow binding of temporary inside transform_demo as current implementation does not ownt the copied / moved range
// so we pass Range& collection just because we are lazy
template <typename Range>
auto transform_demo(Range& collection, std::invocable<std::ranges::range_reference_t<Range>> auto&& invocable)
{
    return collection | std::views::transform(std::forward<decltype(invocable)>(invocable));
}

int main()
{
    std::vector<int> v1{ 1, 2, 3, 4, 5 };
    print_collection(v1);

    spdlog::info("std::accumulate of v1: {}", accumulate_demo(v1));

    auto transformed = transform_demo(v1, [](int elem) { return elem * elem; });
    print_collection(transformed | std::views::reverse);

    return EXIT_SUCCESS;
}
