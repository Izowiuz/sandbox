#include <coroutine>
#include <optional>

#include "spdlog/spdlog.h"

// coroutine return type
struct Generator {
    struct promise_type {
        Generator get_return_object()
        {
            return Generator{ std::coroutine_handle<promise_type>::from_promise(*this) };
        }

        std::suspend_always initial_suspend()
        {
            return {};
        }

        std::suspend_always final_suspend() noexcept
        {
            return {};
        }

        std::suspend_always yield_value(int value)
        {
            current_value = value;
            return {};
        }

        void return_void()
        {
        }

        void unhandled_exception()
        {
            std::terminate();
        }

        std::optional<int> current_value;
    };

    std::coroutine_handle<promise_type> handle;

    explicit Generator(std::coroutine_handle<promise_type> h)
        : handle(h)
    {
    }

    Generator(const Generator&) = delete;

    Generator(Generator&& other) noexcept
        : handle(other.handle)
    {
        other.handle = {};
    }

    ~Generator()
    {
        if (handle) {
            handle.destroy();
        }
    }

    std::optional<int> next()
    {
        if (!handle || handle.done()) {
            return std::nullopt;
        }

        handle.resume();
        return handle.promise().current_value;
    }
};

// infinite Fibonacci coroutine generator
Generator fibonacci()
{
    int a = 0;
    int b = 1;

    while (true) {
        co_yield a;

        int temp = a + b;
        a = b;
        b = temp;
    }
}

int main()
{
    auto gen = fibonacci();
    for (int i = 0; i < 20; ++i) {
        if (auto value = gen.next()) {
            spdlog::info("{}", *value);
        }
    }

    return 0;
}
