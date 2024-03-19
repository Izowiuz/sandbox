#include <cstdlib>
#include <string>

#include <spdlog/spdlog.h>

class Foo
{
public:
    void foo(double, bool = true)
    {
        spdlog::info("double, bool = true");
    }

    void foo(double, std::string const&)
    {
        spdlog::info("double, std::string const&)");
    }
};

int main()
{
    Foo f;

    f.foo(0.0f, "lala");

    return EXIT_SUCCESS;
}
