#include <cstdlib>

#include <spdlog/spdlog.h>

namespace some_namespace
{

class Foo
{
};

void swap(Foo& a, Foo& b) noexcept
{
    spdlog::info("some_namespace::swap");
}

}   // namespace some_namespace

template <class T>
void some_function(T& a, T& b)
{
    using std::swap;
    swap(a, b);
}

int main()
{
    {
        some_namespace::Foo a;
        some_namespace::Foo b;

        spdlog::info("Foo");
        some_function(a, b);
    }

    {
        int a{ 1 };
        int b{ 1 };

        spdlog::info("int");
        some_function(a, b);
    }

    return EXIT_SUCCESS;
}
