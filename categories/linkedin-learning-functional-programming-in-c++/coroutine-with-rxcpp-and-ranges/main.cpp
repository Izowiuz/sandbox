#include <cstdlib>

#include "rxcpp/rx.hpp"
#include <spdlog/spdlog.h>

rxcpp::observable<int> generate_values()
{
    return rxcpp::observable<>::create<int>([](const rxcpp::subscriber<int>& subscriber) {
        for (int i = 0; i < 10; ++i) {
            subscriber.on_next(i);
        }
        subscriber.on_completed();
    });
}

int main()
{
    auto stream = generate_values().filter([](int v) { return v % 2 == 0; });
    stream.subscribe([](int v) { spdlog::info("Recieved: {}", v); }, []() { spdlog::info("Done, yo!"); });

    return EXIT_SUCCESS;
}
