#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <spdlog/spdlog.h>
#include <string>

/*
Write a function which converts the input string to uppercase.
*/

std::string makeUpperCase(const std::string& str)
{
    auto result = str;

    std::transform(result.begin(), result.end(), result.begin(), [](char c) {
        return std::toupper(static_cast<unsigned char>(c));
    });

    return result;
}

int main()
{
    spdlog::info(makeUpperCase("hello world!"));

    return EXIT_SUCCESS;
}
