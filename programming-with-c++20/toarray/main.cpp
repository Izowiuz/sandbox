#include <array>
#include <cstdlib>
#include <typeinfo>

#include "spdlog/spdlog.h"

int main()
{
    std::array<int, 3> const arr1 = { 1, 2, 3 };
    auto const arr2 = std::to_array({ 1, 2, 3 });

    spdlog::info(
        "typeid of arr1: {}, typeid of arr2: {}", typeid(decltype(arr1)).name(), typeid(decltype(arr1)).name());

    return EXIT_SUCCESS;
}
