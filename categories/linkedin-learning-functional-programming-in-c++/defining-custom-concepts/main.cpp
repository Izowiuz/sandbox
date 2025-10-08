#include <concepts>
#include <cstdlib>
#include <string>
#include <vector>

#include "fmt/ranges.h"
#include "spdlog/spdlog.h"

template <typename Container>
concept Iterable = requires(Container t) {
    { t.begin() } -> std::same_as<decltype(t.end())>;
};

template <Iterable T>
void print_container(T const& container)
{
    spdlog::info("container: {}", container);
}

int main()
{
    std::vector<int> v1{ 1, 2, 3, 4, 5 };
    std::vector<std::string> v2{ "h", "e", "l", "l", "o" };

    print_container(v1);
    print_container(v2);
    // does not compile
    // print_container(42);

    return EXIT_SUCCESS;
}
