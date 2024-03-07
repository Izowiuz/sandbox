#include <cstdlib>

class Interface
{
public:
    virtual void func() = 0;
};

class SomeImplementation : public Interface
{
public:
    void func() override
    {
    }
};

class ExternalClass
{
public:
    void relatedFunc()
    {
    }
};

class ClassAdapter : public Interface, private ExternalClass
{
public:
    void func() override
    {
        relatedFunc();
    }
};

int main()
{
    return EXIT_SUCCESS;
}
