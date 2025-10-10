#include <cstdlib>

#include "rxcpp/rx.hpp"
#include "spdlog/spdlog.h"

int main()
{
    auto values = rxcpp::observable<>::range(1, 5);

    values.subscribe([](int v) { spdlog::info("Recieved: {}", v); });

    return EXIT_SUCCESS;
}
