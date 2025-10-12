#include <chrono>
#include <cstdlib>

#include "rxcpp/rx.hpp"
#include "spdlog/spdlog.h"

int main()
{
    auto source = rxcpp::observable<>::interval(std::chrono::milliseconds(500)).take(5).map([](long i) {
        return "Data point: " + std::to_string(i);
    });
    source.subscribe([](std::string const& value) { spdlog::info("Received: {}", value); },
                     []() { spdlog::info("Done, yo!"); });

    return EXIT_SUCCESS;
}
