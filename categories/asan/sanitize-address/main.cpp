#include <cstdlib>

/*
 * Expected to be run with -fsanitize=address
 */

int main()
{
    int* a = new int(1);
    delete a;

    // heap-use-after-free
    *a = 42;

    return EXIT_SUCCESS;
}
