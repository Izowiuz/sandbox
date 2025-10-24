#include <cstdlib>
#include <string>
#include <unordered_map>
#include <vector>

#include "fmt/ranges.h"
#include "rxcpp/rx.hpp"
#include <spdlog/spdlog.h>

int main()
{
    std::vector<std::string> words{ "hello", "world", "hello", "functional", "world", "programming" };
    std::unordered_map<std::string, int> word_count;

    auto stream = rxcpp::observable<>::create<std::string>([&](const rxcpp::subscriber<std::string>& subscriber) {
        for (auto const& w : words) {
            subscriber.on_next(w);
        }
        subscriber.on_completed();
    });

    stream.subscribe(
        [&](std::string const& value) {
            spdlog::info("Recieved: {}", value);
            word_count[value]++;
        },
        []() { spdlog::info("Stream ended!"); });

    for (auto const& [key, value] : word_count) {
        spdlog::info("Word: {}, count: {}", key, value);
    }

    return EXIT_SUCCESS;
}
