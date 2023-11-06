#include <cstdlib>
#include <vector>

#include "spdlog/spdlog.h"

template<typename T, typename... U>
void push_many(std::vector<T>& vec, U&&... e)
{
    auto push_one = [&](auto&& e){
        spdlog::info("pushing: {}", e);
        vec.push_back(std::forward<decltype(e)>(e));
    };

    ( ..., push_one(std::forward<U>(e)) );
}

int main()
{
    std::vector<int> vec;

    push_many(vec, 1, 2, 3, 4);

    return EXIT_SUCCESS;
}
