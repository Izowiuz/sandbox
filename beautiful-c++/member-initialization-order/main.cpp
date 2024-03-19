#include <cstdint>
#include <cstdlib>
#include <string>

#include "spdlog/spdlog.h"

class Foo
{
public:
    // bad ctor - look at the order of members under private specifier
    Foo(std::string string)
        : mString{ std::move(string) }
        , mUint{ stringSize() }
    {
        spdlog::info("string size: {}", mUint);
    }

    std::uint32_t stringSize() const
    {
        return mString.size();
    }

private:
    std::uint32_t mUint;
    std::string mString;
};

int main()
{
    // garbage in mUint member
    Foo f{"lalala"};

    spdlog::info("proper string size: {}", f.stringSize());

    return EXIT_SUCCESS;
}
