#include <cstdlib>

class Interface
{
public:
    virtual ~Interface() = default;
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

class ObjectAdapter final : public Interface
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
