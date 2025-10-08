#include <cstdlib>

#include "spdlog/spdlog.h"

template <typename T>
concept SupportsValidation = requires(T t) {
    { t.validate() } -> std::same_as<bool>;
};

class Message1
{
public:
    bool validate() const
    {
        spdlog::info("yo! Message1 is valid!");
        return true;
    }
};

class Message2
{
    // no validation function
};

class Message3
{
public:
    // incompatible validation function
    int validate() const
    {
        spdlog::info("yo! Message3 is valid!");
        return 0;
    }
};

class Sender
{
public:
    template <typename T>
    void send(T const& message)
    {
        if constexpr (SupportsValidation<T>) {
            spdlog::info("validate result: {}", message.validate());
        } else {
            spdlog::info("no validation required");
        }
    }
};

int main()
{
    Sender sender;
    sender.send(Message1{});
    sender.send(Message2{});
    sender.send(Message3{});

    return EXIT_SUCCESS;
}
