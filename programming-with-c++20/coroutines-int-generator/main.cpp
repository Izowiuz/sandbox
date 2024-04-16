#include <coroutine>
#include <cstdlib>
#include <utility>

#include "spdlog/spdlog.h"

// promise type
template <typename Value, typename Generator>
struct promise_type_base {
    Value value;

    // invoked by co_yield or co_return
    auto yield_value(Value value)
    {
        spdlog::info("yeld_value(): {}", value);
        this->value = std::move(value);
        return std::suspend_always();
    }

    // returns generator
    Generator get_return_object()
    {
        spdlog::info("get_return_object()");
        return Generator(this);
    }

    std::suspend_always initial_suspend()
    {
        spdlog::info("initial_suspend()");
        return {};
    }

    std::suspend_always final_suspend() noexcept
    {
        spdlog::info("initial_suspend()");
        return {};
    }

    void unhandled_exception()
    {
        spdlog::info("unhandled_exception()");
        std::terminate();
    }

    // TODO: fix me?
    // static auto get_return_object_on_allocation_failure()
    // {
    //     spdlog::info("get_return_object_on_allocation_failure()");
    //     return Generator(nullptr);
    // }
};

// coroutine iterator
template <typename PromiseType>
struct coroutine_iterator {

    coroutine_iterator() = default;

    coroutine_iterator(std::coroutine_handle<PromiseType> coroutineHandle)
        : coroutineHandle(coroutineHandle)
    {
        spdlog::info("coroutine_iterator()");
        resume();
    }

    void resume()
    {
        spdlog::info("resume()");
        if (!coroutineHandle.done()) {
            coroutineHandle.resume();
        }
    }

    void operator++()
    {
        spdlog::info("operator++()");
        resume();
    }

    bool operator==(coroutine_iterator const&)
    {
        spdlog::info("operator==()");
        return coroutineHandle.done();
    }

    auto const& operator*() const
    {
        spdlog::info("operator*()");
        return coroutineHandle.promise().value;
    }

    std::coroutine_handle<PromiseType> coroutineHandle;
};

// coroutine generator
template <typename Value>
struct generator {
    using promise_type = promise_type_base<Value, generator>;
    using promise_type_handle = std::coroutine_handle<promise_type>;
    using iterator = coroutine_iterator<promise_type>;

    generator(generator const&) = delete;

    generator(generator&& other) noexcept
        : mCoroutineHandle(std::exchange(other.coroutineHandle, nullptr))
    {
    }

    ~generator()
    {
        // manual promise_type_handle life time
        if (mCoroutineHandle) {
            mCoroutineHandle.destroy();
        }
    }

    iterator begin()
    {
        return { mCoroutineHandle };
    }

    iterator end()
    {
        return {};
    }

private:
    friend promise_type;

    explicit generator(promise_type* promise)
        : mCoroutineHandle(promise_type_handle::from_promise(*promise))
    {
    }

    promise_type_handle mCoroutineHandle;
};

generator<int> generate_numbers(std::size_t start, std::size_t end)
{
    while (start < end) {
        co_yield start;
        ++start;
    }
}

int main()
{
    auto generator = generate_numbers(1, 4);

    for (auto const generatedValue : generator) {
        spdlog::info("generated value: {}", generatedValue);
    }

    return EXIT_SUCCESS;
}
