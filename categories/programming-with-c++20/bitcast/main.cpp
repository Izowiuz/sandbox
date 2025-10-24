#include <bit>
#include <cstdint>
#include <cstdlib>

#include <spdlog/spdlog.h>

int main()
{
    float f{ 42.1F };
    auto i = std::bit_cast<std::uint32_t>(f);
    // does not compile - size mismatch
    // auto i = std::bit_cast<std::uint8_t>(f);

    spdlog::info("f: {} i: {}", f, i);

    return EXIT_SUCCESS;
}
