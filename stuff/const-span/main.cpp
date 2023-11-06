#include <cstdlib>
#include <span>
#include <vector>

int main()
{
    std::vector<int> vectorA{1, 2, 3, 4};

    std::vector<int> vector{1, 2, 3, 4};
    std::span<int> const span{vector};

    span[0] = 1234;

    return EXIT_SUCCESS;
}
