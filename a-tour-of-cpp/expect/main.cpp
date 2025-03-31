#include <concepts>
#include <cstdint>
#include <cstdlib>
#include <exception>
#include <vector>

#include "spdlog/spdlog.h"

enum class Action : std::uint8_t { Terminate, Log };

template <Action action = Action::Log>
constexpr void expect(std::invocable auto&& condition, const char* message)
{
    if constexpr (action == Action::Log) {
        if (!condition()) {
            spdlog::info("expect failed with: \"{}\"", message);
        }
    } else if (action == Action::Terminate) {
        if (!condition()) {
            spdlog::info("expect failed with: \"{}\" - terminating", message);
            std::terminate();
        }
    }
}

void parseVector1(std::vector<int> const& v)
{
    expect([&v]() -> bool { return v.size() > 1 && v.size() < 5; }, ":[");
}

void parseVector2(std::vector<int> const& v)
{
    expect<Action::Terminate>([&v]() -> bool { return v.size() > 1 && v.size() < 5; }, ":[");
}

int main()
{
    std::vector<int> v1{ 1, 2, 3 };
    parseVector1(v1);

    std::vector<int> v2{ 1, 2, 3, 4, 5 };
    parseVector1(v2);

    std::vector<int> v3{ 1, 2, 3, 4, 5 };
    parseVector2(v3);

    return EXIT_SUCCESS;
}
