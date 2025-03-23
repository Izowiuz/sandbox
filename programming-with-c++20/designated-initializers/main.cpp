#include <cstdlib>

struct s
{
    int x;
    int y{2};
    int z;
};

int main()
{
    // braced initialization - every field zero initialized
    s s1{};
    s s2{.x = 1, .z = 3};
    // also braced initialization - z zero initialized
    s s3{.x = 1};
    // does not compile - different order than in declaration
    // s s4{.y = 1, .x = 0, .z = 5};
    
    return EXIT_SUCCESS;
}
