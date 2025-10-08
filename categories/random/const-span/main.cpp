#include <cstdlib>
#include <span>
#include <vector>

#include "spdlog/spdlog.h"

int main()
{
    std::vector<int> vector{ 1, 2, 3, 4 };
    std::span<int> const span{ vector };

    spdlog::info("before: {}", vector[0]);

    span[0] = 1234;

    spdlog::info("after: {}", vector[0]);

    return EXIT_SUCCESS;
}
