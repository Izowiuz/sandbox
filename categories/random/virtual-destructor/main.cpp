#include <cstdlib>

#include <spdlog/spdlog.h>

class VirtualPublicDtor
{
public:
    virtual ~VirtualPublicDtor()
    {
        spdlog::info("~VirtualPublicDtor()");
    }
};

class PublicDtor
{
public:
    ~PublicDtor()
    {
        spdlog::info("~PublicDtor()");
    }
};

class ProtectedDtor
{
protected:
    ~ProtectedDtor()
    {
        spdlog::info("~ProtectedDtor()");
    }
};

class Foo : public VirtualPublicDtor
{
public:
    ~Foo()
    {
        spdlog::info("~Foo()");
    }
};

class Bar : public PublicDtor
{
public:
    ~Bar()
    {
        spdlog::info("~Bar()");
    }
};

class Sth : public ProtectedDtor
{
public:
    ~Sth()
    {
        spdlog::info("~Sth()");
    }
};

int main()
{
    VirtualPublicDtor* virtualdtor = new Foo;
    delete virtualdtor;

    PublicDtor* nonvirtualdtor = new Bar;
    delete nonvirtualdtor;

    ProtectedDtor* protecteddtor = new Sth;
    // will not compile
    // delete protecteddtor;
    delete static_cast<Sth*>(protecteddtor);

    return EXIT_SUCCESS;
}
