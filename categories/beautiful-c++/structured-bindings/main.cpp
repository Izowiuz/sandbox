#include <cstdint>
#include <cstdlib>
#include <string>

#include <spdlog/spdlog.h>

struct Foo {
    std::string string;
    std::int32_t integer;
};

Foo foo(std::string const& string, std::int32_t integer)
{
    return Foo{ .string = string, .integer = integer };
}

int main()
{
    const auto [string, integer] = foo("lalala", 42);

    spdlog::info("string: {}, integer: {}", string, integer);

    return EXIT_SUCCESS;
}
