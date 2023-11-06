#include <cstdlib>
#include <functional>
#include <iostream>

#include "spdlog/spdlog.h"

class Base
{
public:
    virtual ~Base() = default;

    virtual void sayHello() const = 0;
};

class Foo : public Base
{
public:
    using HelloStrategy = std::function<void(Foo const&)>;

    explicit Foo(HelloStrategy helloStrategy)
        : mHelloStrategy{ std::move(helloStrategy) }
    {
    }

    void sayHello() const override
    {
        mHelloStrategy(*this);
    }

private:
    HelloStrategy mHelloStrategy;
};

class SpdlogFooHelloStrategy
{
public:
    void operator()(Foo const&)
    {
        spdlog::info("Say hello from Foo with spdlog!");
    }
};

class IOStreamFooHelloStrategy
{
public:
    void operator()(Foo const&)
    {
        std::cout << "Say hello from Foo with IOStream!" << std::endl;
    }
};

int main()
{
    std::vector<std::unique_ptr<Base>> classes;
    classes.emplace_back(std::make_unique<Foo>(SpdlogFooHelloStrategy()));
    classes.emplace_back(std::make_unique<Foo>(IOStreamFooHelloStrategy()));

    for (const auto& c : classes) {
        c->sayHello();
    }

    return EXIT_SUCCESS;
}
