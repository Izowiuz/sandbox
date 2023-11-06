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

class ObjectAdapter : public Interface
{
public:
    void func() override
    {
        mExternal.relatedFunc();
    }

private:
    ExternalClass mExternal;
};

int main()
{
    return EXIT_SUCCESS;
}
