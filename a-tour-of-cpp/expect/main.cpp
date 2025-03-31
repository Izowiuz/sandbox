#include <concepts>
#include <cstdint>
#include <cstdlib>
#include <exception>
#include <source_location>
#include <vector>

#include "spdlog/spdlog.h"

enum class Action : std::uint8_t { Nothing, Log, Terminate };

template <Action action = Action::Log>
constexpr void expect(std::invocable auto&& condition,
                      const char* message,
                      const std::source_location loc = std::source_location::current())
{
    if constexpr (action == Action::Log) {
        if (!condition()) {
            spdlog::info("expect failed with: \"{}\" at: {}", message, loc.function_name());
        }
    } else if (action == Action::Terminate) {
        if (!condition()) {
            spdlog::info("expect failed with: \"{}\" at: {} - terminating", message, loc.function_name());
            std::terminate();
        }
    }
}

template <Action action>
void parseVector(std::vector<int> const& v)
{
    expect<action>([&v]() -> bool { return v.size() > 1 && v.size() < 5; }, ":[");
}

int main()
{
    std::vector<int> vecOk{ 1, 2, 3 };
    std::vector<int> vecNOk{ 1, 2, 3, 4, 5 };

    // conditions ok
    parseVector<Action::Log>(vecOk);

    // conditions not ok - log
    parseVector<Action::Log>(vecNOk);

    // conditions not ok - nothing
    parseVector<Action::Nothing>(vecNOk);

    // conditions not ok - terminate
    parseVector<Action::Terminate>(vecNOk);

    return EXIT_SUCCESS;
}
