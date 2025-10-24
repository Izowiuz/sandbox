#include <cstdlib>
#include <mutex>

#include <spdlog/spdlog.h>

class Foo
{
public:
    void doSomethingWithResource(std::invocable<int&> auto&& func)
    {
        std::lock_guard lock(mResourceMutex);
        func(mResource);
    }

    void doSomethingWithResourceV2(std::invocable<int&> auto&& func)
    {
        if (auto lock = std::unique_lock(mResourceMutex, std::try_to_lock)) {
            spdlog::info(":D");
            func(mResource);
        } else {
            spdlog::info(":[");
        }
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
    f.doSomethingWithResource([&f](auto& s) { s = 42; });
    spdlog::info("f.resource(): {}", f.resource());

    f.doSomethingWithResourceV2([&f](auto& s) { f.doSomethingWithResourceV2([](auto s) {}); });

    return EXIT_SUCCESS;
}
