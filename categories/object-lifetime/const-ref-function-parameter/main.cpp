#include <cstdlib>

#include <spdlog/spdlog.h>

class foo
{
public:
    foo()
    {
        spdlog::info("foo()");
    }

    ~foo()
    {
        spdlog::info("~foo()");
    }

    foo([[maybe_unused]] const foo& other)
    {
        spdlog::info("foo(const foo& other)");
    }

    foo([[maybe_unused]] foo&& other) noexcept
    {
        spdlog::info("foo(foo&& other)");
    }

    foo& operator=([[maybe_unused]] const foo& other)
    {
        spdlog::info("operator=(const foo& other)");
        return *this;
    }

    foo& operator=([[maybe_unused]] foo&& other) noexcept
    {
        spdlog::info("operator=(foo&& other)");
        return *this;
    }
};

void bar([[maybe_unused]] const foo& f)
{
    spdlog::info("bar(const foo& f)");
}


int main()
{
    spdlog::info("main()");

    bar(foo{});

    return EXIT_SUCCESS;
}
