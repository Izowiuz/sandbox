#include <cstdlib>
#include <string>

#include "boost/hana.hpp"
#include <spdlog/spdlog.h>

int main()
{
    auto my_tuple = boost::hana::make_tuple(10, "hello", 3.14);
    auto transformed_tuple = boost::hana::transform(my_tuple, [](auto x) {
        if constexpr (std::is_same_v<decltype(x), const char*>) {
            std::string str(x);
            return str + " - " + str;
        } else {
            return x + x;
        }
    });

    boost::hana::for_each(transformed_tuple, [](auto x) { spdlog::info("x: {}", x); });

    return EXIT_SUCCESS;
}
