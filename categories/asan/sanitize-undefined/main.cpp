#include <cstdlib>
#include <limits>

/*
 * Expected to be run with -fsanitize=undefined
 */

int main()
{
    int a = std::numeric_limits<int>::max();
    a += 1;

    return EXIT_SUCCESS;
}
