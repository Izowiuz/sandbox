#include <chrono>
#include <cstdlib>
#include <functional>
#include <future>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include "spdlog/spdlog.h"

using event_handler = std::function<void(std::string const&)>;

auto simulate_event_source(event_handler handler) -> std::vector<std::future<void>>
{
    std::vector<std::string> events = { "e1", "e2", "e3", "e4", "e5" };

    std::vector<std::future<void>> futures;
    futures.reserve(events.size());

    for (auto const& event : events) {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        futures.push_back(std::async(std::launch::async, handler, event));
    }

    return futures;
}

int main()
{
    event_handler function_handler = [](std::string const& event) {
        std::stringstream ss;
        ss << std::this_thread::get_id();
        auto const thread_id_str = ss.str();
        spdlog::info("Got event: {}, from thread: {}", event, thread_id_str);
    };

    auto safe_function_handler = [&](std::string const& event) {
        try {
            function_handler(event);
        } catch (std::exception const& e) {
            spdlog::info("Exception in handle: {}", e.what());
        }
    };

    auto const futures = simulate_event_source(safe_function_handler);

    spdlog::info("End of main!");

    return EXIT_SUCCESS;
}
