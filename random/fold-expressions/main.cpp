#include <cstdlib>
#include <vector>

#include "spdlog/spdlog.h"

template <typename T, typename... U>
void push_many(std::vector<T>& vec, U&&... e)
{
    spdlog::info("Current capacity: {} increase by: {}", vec.capacity(), sizeof...(U));
    vec.reserve(vec.capacity() + sizeof...(U));

    auto push_one = [&](auto&& e) {
        spdlog::info("pushing: {}", e);
        vec.push_back(std::forward<decltype(e)>(e));
    };

    (..., push_one(std::forward<U>(e)));
}

int main()
{
    std::vector<int> vec;

    push_many(vec, 1, 2, 3, 4);
    push_many(vec, 5, 6);

    return EXIT_SUCCESS;
}
