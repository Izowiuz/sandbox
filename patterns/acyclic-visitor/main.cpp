#include <cstdlib>

#include <spdlog/spdlog.h>

class AbstractVisitor
{
public:
    virtual ~AbstractVisitor() = default;
};

template <class T>
class Visitor
{
protected:
    ~Visitor() = default;

public:
    virtual void visit(T const&) const = 0;
};

class Base
{
public:
    Base(std::string name)
        : mName{ std::move(name) }
    {
    }

    virtual ~Base() = default;

    virtual void accept(AbstractVisitor const&) const = 0;

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

    void accept(AbstractVisitor const& v) const override
    {
        if (auto const* casted = dynamic_cast<Visitor<First> const*>(&v)) {
            casted->visit(*this);
        }
    }
};

class Second : public Base
{
public:
    Second()
        : Base("Second!")
    {
    }

    void accept(AbstractVisitor const& v) const override
    {
        if (auto const* casted = dynamic_cast<Visitor<Second> const*>(&v)) {
            casted->visit(*this);
        }
    }
};

class SayHello : public AbstractVisitor, public Visitor<First>, public Visitor<Second>
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
