#include <cstdlib>
#include <variant>
#include <vector>

#include <spdlog/spdlog.h>

class Base
{
public:
    explicit Base(std::string name)
        : mName{ std::move(name) }
    {
    }

    virtual ~Base() = default;

    std::string me() const
    {
        return mName;
    }

private:
    std::string mName;
};

class First : public Base
{
public:
    First()
        : Base("First!")
    {
    }
};

class Second : public Base
{
public:
    Second()
        : Base("Second!")
    {
    }
};

struct SayHello {
    void operator()(First const& f)
    {
        spdlog::info("Hello from: {}", f.me());
    }

    void operator()(Second const& s)
    {
        spdlog::info("Hello from: {}", s.me());
    }
};

using Classes = std::vector<std::variant<First, Second>>;

int main()
{
    Classes cls;
    cls.emplace_back(First{});
    cls.emplace_back(Second{});

    for (const auto& e : cls) {
        std::visit(SayHello{}, e);
    }

    return EXIT_SUCCESS;
}
