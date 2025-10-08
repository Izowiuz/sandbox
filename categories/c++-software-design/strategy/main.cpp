#include <cstdlib>
#include <iostream>
#include <memory>
#include <vector>

#include "spdlog/spdlog.h"

template <typename T>
class HelloStrategy
{
public:
    virtual ~HelloStrategy() = default;

    virtual void sayHello() const = 0;
};

class Foo;

class SpdlogFooHelloStrategy final : public HelloStrategy<Foo>
{
public:
    void sayHello() const override
    {
        spdlog::info("Say hello from Foo with spdlog!");
    }
};

class IOStreamFooHelloStrategy final : public HelloStrategy<Foo>
{
public:
    void sayHello() const override
    {
        std::cout << "Say hello from Foo with IOStream!" << '\n';
    }
};

class Base
{
public:
    virtual ~Base() = default;

    virtual void sayHello() const = 0;
};

class Foo : public Base
{
public:
    explicit Foo(std::unique_ptr<HelloStrategy<Foo>> helloStrategy)
        : mHelloStrategy{ std::move(helloStrategy) }
    {
    }

    void sayHello() const override
    {
        mHelloStrategy->sayHello();
    }

private:
    std::unique_ptr<HelloStrategy<Foo>> mHelloStrategy;
};

int main()
{
    std::vector<std::unique_ptr<Base>> classes;
    classes.emplace_back(std::make_unique<Foo>(std::make_unique<SpdlogFooHelloStrategy>()));
    classes.emplace_back(std::make_unique<Foo>(std::make_unique<IOStreamFooHelloStrategy>()));

    for (const auto& c : classes) {
        c->sayHello();
    }

    return EXIT_SUCCESS;
}
