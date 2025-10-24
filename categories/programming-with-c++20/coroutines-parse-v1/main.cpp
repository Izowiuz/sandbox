#include <cassert>
#include <coroutine>
#include <cstdlib>
#include <optional>
#include <string>
#include <vector>

#include <spdlog/spdlog.h>

static const std::byte ESC{ 'H' };
static const std::byte SOF{ 0x10 };

std::byte operator""_B(char c)
{
    return static_cast<std::byte>(c);
}
std::byte operator""_B(unsigned long long c)
{
    return static_cast<std::byte>(c);
}

template <typename Value, typename Generator, typename... Bases>
struct promise_type_base : public Bases... {
    Value mValue;

    auto yield_value(Value value)
    {
        mValue = std::move(value);
        return std::suspend_always{};
    }

    Generator get_return_object()
    {
        return Generator{ this };
    }

    std::suspend_always initial_suspend()
    {
        return {};
    }

    std::suspend_always final_suspend() noexcept
    {
        return {};
    }

    void return_void()
    {
    }

    void unhandled_exception()
    {
        std::terminate();
    }
};

template <typename Signal>
struct awaitable_promise_type_base {
    std::optional<Signal> mRecentSignal;

    struct awaiter {
        std::optional<Signal>& mRecentSignal;

        bool await_ready() const
        {
            return mRecentSignal.has_value();
        }

        void await_suspend(std::coroutine_handle<>)
        {
        }

        Signal await_resume()
        {
            assert(mRecentSignal.has_value());
            auto tmp = std::move(*mRecentSignal);
            mRecentSignal.reset();
            return tmp;
        }
    };

    [[nodiscard]] awaiter await_transform(Signal)
    {
        return awaiter(mRecentSignal);
    }
};

template <typename Value, typename Signal>
struct async_generator {
    using promise_type = promise_type_base<Value, async_generator, awaitable_promise_type_base<Signal>>;
    using promise_type_handle = std::coroutine_handle<promise_type>;

    Value operator()()
    {
        // move the value
        auto tmp{ std::move(mCoroutineHandle.promise().mValue) };

        // ensure defined state after move
        mCoroutineHandle.promise().mValue.clear();

        return tmp;
    }

    void sendSignal(Signal signal)
    {
        spdlog::info("signal: {}", static_cast<char>(signal));

        mCoroutineHandle.promise().mRecentSignal = std::move(signal);

        if (!mCoroutineHandle.done()) {
            mCoroutineHandle.resume();
        }
    }

    async_generator(async_generator const&) = delete;
    async_generator(async_generator&& generator) noexcept
        : mCoroutineHandle{ std::exchange(generator, nullptr) }
    {
    }

    ~async_generator()
    {
        if (mCoroutineHandle) {
            mCoroutineHandle.destroy();
        }
    }

private:
    friend promise_type;

    explicit async_generator(promise_type* p)
        : mCoroutineHandle(promise_type_handle::from_promise(*p))
    {
    }

    promise_type_handle mCoroutineHandle;
};

template <typename PromiseType>
struct coroutine_iterator {

    coroutine_iterator() = default;

    coroutine_iterator(std::coroutine_handle<PromiseType> coroutineHandle)
        : coroutineHandle(coroutineHandle)
    {
        resume();
    }

    void resume()
    {
        if (!coroutineHandle.done()) {
            coroutineHandle.resume();
        }
    }

    void operator++()
    {
        resume();
    }

    bool operator==(coroutine_iterator const&)
    {
        return coroutineHandle.done();
    }

    // [ ... ? ]
    bool operator!=(coroutine_iterator const&)
    {
        return !coroutineHandle.done();
    }

    auto const& operator*() const
    {
        return coroutineHandle.promise().mValue;
    }

    std::coroutine_handle<PromiseType> coroutineHandle;
};

template <typename Value>
struct generator {
    using promise_type = promise_type_base<Value, generator>;
    using promise_type_handle = std::coroutine_handle<promise_type>;
    using iterator = coroutine_iterator<promise_type>;

    generator(generator const&) = delete;

    generator(generator&& other) noexcept
        : mCoroutineHandle(std::exchange(other.mCoroutineHandle, nullptr))
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

using FSM = async_generator<std::string, std::byte>;

FSM parse()
{
    while (true) {
        std::byte b = co_await std::byte{};
        if (ESC != b) {
            continue;
        }

        b = co_await std::byte{};
        if (SOF != b) {
            continue;
        }

        std::string frame;

        while (true) {
            b = co_await std::byte{};
            if (ESC == b) {
                b = co_await std::byte{};

                if (SOF == b) {
                    spdlog::info("yield!");

                    co_yield frame;
                    break;
                } else if (b != ESC) {
                    break;
                }
            }

            frame += static_cast<char>(b);
        }
    }
}

generator<std::byte> sender(std::vector<std::byte>&& fakeBytes)
{
    for (auto const& b : fakeBytes) {
        co_yield b;
    }
}

void handleFullFrame(const std::string& frame)
{
    spdlog::info("full frame: {}", frame);
}

void processStream(generator<std::byte>& stream, FSM& parse)
{
    for (auto const& b : stream) {
        parse.sendSignal(b);
    }

    if (auto const& res = parse(); res.length() > 0) {
        handleFullFrame(res);
    }
}

int main()
{
    std::vector<std::byte> fakeBytes1{ 0x70_B, ESC,   SOF, ESC, 'H'_B, 'e'_B, 'l'_B,
                                       'l'_B,  'o'_B, ESC, SOF, 0x7_B, ESC,   SOF };

    // simulate the first network stream
    auto stream1 = sender(std::move(fakeBytes1));

    // create the Parse coroutine and store the handle in p
    auto p = parse();

    // process the bytes
    processStream(stream1, p);

    // Simulate the reopening of the network stream
    std::vector<std::byte> fakeBytes2{ 'W'_B, 'o'_B, 'r'_B, 'l'_B, 'd'_B, ESC, SOF, 0x99_B };

    // simulate a second network stream
    auto stream2 = sender(std::move(fakeBytes2));

    // we still use the former p and feed it with new bytes
    processStream(stream2, p);

    return EXIT_SUCCESS;
}
