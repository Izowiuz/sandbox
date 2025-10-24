#include <cstdlib>
#include <string>

#include <spdlog/spdlog.h>

struct f1 {
    int a;
    float b;
    std::string c;

    // partial ordering
    auto operator<=>(f1 const &) const = default;
};

struct f2 {
    int a;
    std::string c;

    // strong ordering
    auto operator<=>(f2 const &) const = default;
};

int main()
{
    f1 f1_a = {.a = 1, .b = 2.0F, .c = "1"};
    f1 f1_b = {.a = 2, .b = 2.0F, .c = "1"};
    f1 f1_c = {.a = 2, .b = 2.0F, .c = "0"};

    spdlog::info("f1_a < f1_b: {}", f1_a < f1_b);
    spdlog::info("f1_c > f1_b: {}", f1_c > f1_b);

    return EXIT_SUCCESS;
}
