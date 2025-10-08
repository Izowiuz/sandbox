#include <array>
#include <cstdlib>

#include "spdlog/spdlog.h"

template <typename T, int N, int M>
using Matrix = std::array<std::array<T, N>, M>;

consteval auto matrix_multiply(Matrix<int, 2, 2>& a, Matrix<int, 2, 2>& b)
{
    // TODO: reimplementation
    // std::array<std::array<int, 2>, 2> result = {};

    // for (int i = 0; i < 2; i++) {
    //     for (int j = 0; j < 2; j++) {
    //         result[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j];
    //     }
    // }
    // return result;
    return 0;
}

int main()
{
    std::array<int, 3> a;

    return EXIT_SUCCESS;
}
