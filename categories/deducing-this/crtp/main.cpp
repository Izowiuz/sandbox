#include <cstdlib>

#include "spdlog/spdlog.h"

class Foo
{
public:
    template <typename Self>
    void interface_function(this Self&& self)
    {
        std::forward<Self>(self).implementation();
    }
};

class Bar : public Foo
{
public:
    void implementation()
    {
        spdlog::info("Bar::implementation()");
    }
};

int main()
{
    Bar b;
    b.interface_function();

    return EXIT_SUCCESS;
}
