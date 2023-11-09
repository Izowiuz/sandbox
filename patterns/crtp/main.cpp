#include <cstdlib>

template <typename Derived>
class DenseVector
{
protected:
    // no resources to release and no polymorphic delete is needed - no need for public or virtual dtor
    ~DenseVector() = default;

public:
    Derived& derived()
    {
        return static_cast<Derived&>(*this);
    }

    Derived const& derived() const
    {
        return static_cast<Derived const&>(*this);
    }

    std::size_t size() const
    {
        return derived().size();
    }

    decltype(auto) operator[](std::size_t index)
    {
        return derived()[index];
    }

    decltype(auto) operator[](std::size_t index) const
    {
        return derived()[index];
    }

    decltype(auto) begin()
    {
        return derived().begin();
    }

    decltype(auto) begin() const
    {
        return derived().begin();
    }

    decltype(auto) end()
    {
        return derived().end();
    }

    decltype(auto) end() const
    {
        return derived().end();
    }
};

int main()
{
    return EXIT_SUCCESS;
}
