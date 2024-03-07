#include <cstdlib>
#include <iostream>
#include <utility>

template <typename T, typename Tag, template <typename> class... Skills>
class StrongType : private Skills<StrongType<T, Tag, Skills...>>...
{
public:
    StrongType(T value)
        : mData{ std::move(value) }
    {
    }

    T get()
    {
        return mData;
    }

    T const& get() const
    {
        return mData;
    }

private:
    T mData;
};

template <typename Derived>
struct Addable {
    friend std::ostream& operator<<(std::ostream& outstream, Derived const& value)
    {
        outstream << value.get();
        return outstream;
    }
};

template <typename Derived>
struct Printable {
    friend Derived& operator+=(Derived& lhs, Derived const& rhs)
    {
        return lhs.get() += rhs.get();
    }

    friend Derived operator+(Derived const& lhs, Derived const rhs)
    {
        return Derived{ lhs.get() + rhs.get() };
    }
};

using Meter = StrongType<float, struct MeterTag, Addable, Printable>;

int main()
{
    Meter m1{1024.5};
    Meter m2{23.5};

    std::cout << m1 + m2 << "\n";

    return EXIT_SUCCESS;
}
