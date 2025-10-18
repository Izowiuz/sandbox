#include <cstdlib>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "fmt/ranges.h"
#include "spdlog/spdlog.h"

template <typename T>
concept CanSayHello = requires(T const& t) {
    { t.sayHello() } -> std::same_as<void>;
};

class Erased final
{
public:
    // ctor
    template <typename T>
        requires(CanSayHello<T>)
    explicit Erased(T&& object)
        // we require move ctor for T
        : mObjectPtr{ new T(std::forward<T>(object)), [](void* object) { delete static_cast<T*>(object); } }
    {
        // our pretty, handmade vtable
        static const Interface interface = { [](void const* object) { static_cast<T const*>(object)->sayHello(); } };
        mInterface = &interface;
    };

    // move ctor
    Erased(Erased&& other) noexcept
        : mObjectPtr{ std::move(other.mObjectPtr) }
        , mInterface{ std::exchange(other.mInterface, nullptr) }
    {
    }

    // move assignment
    Erased& operator=(Erased&& other) noexcept
    {
        if (this != &other) {
            mObjectPtr = std::exchange(other.mObjectPtr, nullptr);
            mInterface = std::exchange(other.mInterface, nullptr);
        }
        return *this;
    }

    // no copy
    Erased(const Erased&) = delete;
    Erased& operator=(const Erased&) = delete;

    void sayHello() const
    {
        mInterface->sayHello(mObjectPtr.get());
    }

private:
    using SayHelloFunc = void (*)(void const*);

    struct Interface {
        SayHelloFunc sayHello = nullptr;
        void (*destroy)(void*) = nullptr;
    };

    std::unique_ptr<void, void (*)(void*)> mObjectPtr{ nullptr, [](void*) {} };
    Interface const* mInterface{ nullptr };
};

class ErasedContainer
{
public:
    template <typename T>
    void add(T&& t)
    {
        mData.emplace_back(std::forward<T>(t));
    }

    auto dataSize() const
    {
        return mData.size();
    }

    void allSayHello() const
    {
        for (auto const& e : mData) {
            e.sayHello();
        }
    }

private:
    std::vector<Erased> mData;
};

class A
{
public:
    void sayHello() const
    {
        spdlog::info("A::sayHello -> {}", mString);
    }

    ~A()
    {
        spdlog::info("fff");
    }

private:
    std::string mString{ "lalala" };
};

class B
{
public:
    void sayHello() const
    {
        spdlog::info("B::sayHello -> {}", mInt);
    }

private:
    int mInt{ 42 };
};

class C
{
public:
    void sayHello() const
    {
        spdlog::info("C::sayHello -> {}", mVector);
    }

private:
    std::vector<int> mVector{ 1, 2, 3 };
};

int main()
{
    ErasedContainer c;

    c.add(A{});
    c.add(B{});
    c.add(C{});

    spdlog::info("ErasedContainer size: {}", c.dataSize());

    c.allSayHello();

    return EXIT_SUCCESS;
}
