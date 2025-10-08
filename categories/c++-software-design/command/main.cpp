#include <cstdlib>

#include "spdlog/spdlog.h"

class Command
{
public:
    virtual ~Command() = default;

    virtual void execute() = 0;
};

class CommandExecutor
{
public:
    void execute(Command&& cmd)
    {
        std::move(cmd).execute();
    }
};

class FooCommand final : public Command
{
public:
    void execute() override
    {
        spdlog::info("Foo, yo!");
    }
};

class BarCommand final : public Command
{
public:
    void execute() override
    {
        spdlog::info("Bar, yo!");
    }
};

int main()
{
    CommandExecutor ex;

    ex.execute(FooCommand{});
    ex.execute(BarCommand{});

    return EXIT_SUCCESS;
}
