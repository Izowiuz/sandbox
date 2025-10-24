#include <cstdlib>
#include <vector>

#include <spdlog/spdlog.h>

void f(std::vector<int> const& v)
{
    if (auto const n = v.size(); n < 3) {
        spdlog::info("n < 3: {}", n);
    } else {
        spdlog::info("n > 3: {}", n);
    }
}

int main()
{
    std::vector<int> const a{ 1, 2 };
    std::vector<int> const b{ 1, 2, 3 };
    std::vector<int> const c{ 1, 2, 3, 4, 5 };

    f(a);
    f(b);
    f(c);

    return EXIT_SUCCESS;
}
