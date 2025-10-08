#include <cstdlib>
#include <memory>
#include <string>
#include <vector>

#include <spdlog/spdlog.h>

class BaseVisitor;

class Base
{
public:
    Base(std::string name)
        : mName{ std::move(name) }
    {
    }

    virtual ~Base() = default;

    virtual void accept(BaseVisitor const&) const = 0;

    std::string me() const
    {
        return mName;
    }

private:
    std::string mName;
};

class First;
class Second;

class BaseVisitor
{
public:
    virtual ~BaseVisitor() = default;

    virtual void visit(First const&) const = 0;
    virtual void visit(Second const&) const = 0;
};

class First : public Base
{
public:
    First()
        : Base("First!")
    {
    }

    void accept(BaseVisitor const& v) const override
    {
        v.visit(*this);
    }
};

class Second : public Base
{
public:
    Second()
        : Base("Second!")
    {
    }

    void accept(BaseVisitor const& v) const override
    {
        v.visit(*this);
    }
};

class SayHello final : public BaseVisitor
{
public:
    void visit(First const& f) const override
    {
        spdlog::info("Hello from: {}", f.me());
    }

    void visit(Second const& s) const override
    {
        spdlog::info("Hello from: {}", s.me());
    }
};

int main()
{
    std::vector<std::unique_ptr<Base>> collection;
    collection.reserve(2);

    collection.push_back(std::make_unique<First>());
    collection.push_back(std::make_unique<Second>());

    for (const auto& e : collection) {
        e->accept(SayHello{});
    }

    return EXIT_SUCCESS;
}
