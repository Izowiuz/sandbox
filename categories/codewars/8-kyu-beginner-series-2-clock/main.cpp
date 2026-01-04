#include <cstdlib>
#include <chrono>

#include <spdlog/spdlog.h>

/*
Clock shows h hours, m minutes and s seconds after midnight.

Your task is to write a function which returns the time since midnight in milliseconds.
Example:

h = 0
m = 1
s = 1

result = 61000

Input constraints:

    0 <= h <= 23
    0 <= m <= 59
    0 <= s <= 59
*/

int past(int h, int m, int s) {
    std::chrono::hours const hours{ h };
    std::chrono::minutes const minutes{ m };
    std::chrono::seconds const seconds{ s };

    return static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(hours + minutes + seconds).count());
}

int main()
{
    spdlog::info(past(0, 1, 1));

    return EXIT_SUCCESS;
}
