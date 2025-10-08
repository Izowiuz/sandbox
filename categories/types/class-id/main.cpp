#include <cstdlib>

#include <spdlog/spdlog.h>

struct TypeID {
    static inline size_t mCounter{ 0 };

public:
    template <typename T>
    static size_t id()
    {
        static size_t id = TypeID::mCounter++;
        return id;
    }
};

class Foo
{
};

class Bar
{
};

class Barer
{
};

int main()
{
    Foo a;
    Bar b;
    Barer c;

    spdlog::info("a: {}", TypeID::id<Foo>());
    spdlog::info("b: {}", TypeID::id<Bar>());
    spdlog::info("c: {}", TypeID::id<Barer>());

    return EXIT_SUCCESS;
}
