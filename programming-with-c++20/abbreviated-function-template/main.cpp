#include <cstdlib>
#include <mutex>

#include "spdlog/spdlog.h"

class Foo
{
public:
    void doSomethingWithResource(std::invocable<int&> auto&& func)
    {
        std::lock_guard lock(mResourceMutex);
        func(mResource);
    }

    int resource() const
    {
        std::lock_guard lock(mResourceMutex);
        return mResource;
    }

private:
    int mResource{ 56 };
    mutable std::mutex mResourceMutex;
};

int main()
{
    Foo f;

    spdlog::info("f.resource(): {}", f.resource());
    f.doSomethingWithResource([](auto & s){
        s = 42;
    });
    spdlog::info("f.resource(): {}", f.resource());

    return EXIT_SUCCESS;
}
