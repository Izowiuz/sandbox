#include <cstdlib>
#include <string>
#include <type_traits>
#include <vector>

#include "spdlog/spdlog.h"

class Foo
{
public:
    std::string name;
    std::vector<int> heavyAndImportantVector;
};

class FooFactory final
{
public:
    auto&& setName(this auto&& self, std::string name)
    {
        self.foo.name = std::move(name);
        return std::forward<decltype(self)>(self);
    }

    auto&& setImportantVector(this auto&& self, std::vector<int> vector)
    {
        self.foo.heavyAndImportantVector = std::move(vector);
        return std::forward<decltype(self)>(self);
    }

    [[nodiscard]] Foo build(this auto&& self)
    {
        // debug check only
        if constexpr (std::is_lvalue_reference_v<decltype(self)>) {
            spdlog::info("std::is_lvalue_reference_v<Self>");
        } else if (std::is_rvalue_reference_v<decltype(self)>) {
            spdlog::info("std::is_rvalue_reference_v<Self>");
        } else {
            spdlog::info(":[");
        }

        return std::move(self.foo);
    }

private:
    Foo foo;
};

int main()
{
    FooFactory factory;
    factory.setName("lalala");
    factory.setImportantVector({ 1, 3, 4, 6 });

    spdlog::info("hopefully calling build() in a lvalue context ...");
    auto foo_1 = factory.build();

    spdlog::info("hopefully calling build() in a rvalue context ...");
    auto foo_2 = FooFactory{}.setName("alala").setImportantVector({ 4, 6, 7 }).build();

    return EXIT_SUCCESS;
}
