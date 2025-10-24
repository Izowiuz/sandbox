#include <cstddef>
#include <cstdlib>
#include <vector>

#include <spdlog/spdlog.h>

int main()
{
    std::vector<int> const v = {123, 43, 234, 532};

    for(std::size_t i{0}; auto const & e : v) {
        spdlog::info("element: {}, i: {}", e, i);
        i++;
    }

    return EXIT_SUCCESS;
}
