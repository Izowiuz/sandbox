#include <cstdlib>
#include <string>
#include <vector>

#include <spdlog/spdlog.h>

class Foo
{
public:
    std::string name;
    std::vector<int> heavyAndImportantVector;
};

class FooFactory final
{
public:
    FooFactory& setName(std::string name) &
    {
        foo.name = std::move(name);
        return *this;
    }

    FooFactory&& setName(std::string name) &&
    {
        foo.name = std::move(name);
        return std::move(*this);
    }

    FooFactory& setImportantVector(std::vector<int> vector) &
    {
        foo.heavyAndImportantVector = std::move(vector);
        return *this;
    }

    FooFactory&& setImportantVector(std::vector<int> vector) &&
    {
        foo.heavyAndImportantVector = std::move(vector);
        return std::move(*this);
    }

    Foo build() &
    {
        spdlog::info("Foo build() &");
        return foo;
    }

    Foo build() &&
    {
        spdlog::info("Foo build() &&");
        return std::move(foo);
    }

private:
    Foo foo;
};

int main()
{
    FooFactory factory;
    factory.setName("lalala");
    factory.setImportantVector({ 1, 3, 4, 6 });

    spdlog::info("hopefully calling Foo build() & ...");
    auto foo_1 = factory.build();

    spdlog::info("hopefully calling Foo build() && ...");
    auto foo_2 = FooFactory{}.setName("alala").setImportantVector({ 4, 6, 7 }).build();

    return EXIT_SUCCESS;
}
