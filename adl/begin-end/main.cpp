#include <cstdlib>
#include <iterator>
#include <string>
#include <vector>

#include <spdlog/spdlog.h>

namespace n
{
class Foo
{
public:
    Foo()
        : mVec{ { "a", "b", "c" } }
    {
    }


private:
    friend auto begin(const Foo& foo);
    friend auto end(const Foo& foo);

    std::vector<std::string> mVec;
};

auto begin(const n::Foo& foo)
{
    return foo.mVec.begin();
}

auto end(const n::Foo& foo)
{
    return foo.mVec.end();
}

}   // namespace n

template <class Range>
void traverseRange(const Range& r)
{
    using std::begin;
    using std::end;

    for (auto pos = begin(r); pos != end(r); ++pos) {
        spdlog::info(*pos);
    }
}

int main()
{
    const auto range_1 = std::vector<int>{ 1, 2, 3, 4 };
    const auto range_2 = n::Foo();

    traverseRange(range_1);
    traverseRange(range_2);

    return EXIT_SUCCESS;
}
