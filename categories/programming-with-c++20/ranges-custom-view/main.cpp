#include <cstdlib>
#include <ranges>
#include <vector>

#include "spdlog/spdlog.h"

// custom view
template <std::ranges::view Range>
class custom_take_view : public std::ranges::view_interface<custom_take_view<Range>>
{
    Range mBase{};
    std::ranges::range_difference_t<Range> mCount{};

public:
    custom_take_view() = default;

    constexpr custom_take_view(Range&& range, std::ranges::range_difference_t<Range> count)
        : mBase{ std::move(range) }
        , mCount{ count }
    {
    }

    // view_interface interface
    constexpr Range base() const&
    {
        return mBase;
    }

    constexpr Range base() &&
    {
        return std::move(mBase);
    }

    constexpr auto begin()
    {
        return std::ranges::begin(mBase);
    }

    constexpr auto end()
    {
        return std::ranges::next(std::ranges::begin(mBase), mCount);
    }
};

// deduction guide
template <std::ranges::range Range>
custom_take_view(Range&& range, std::ranges::range_difference_t<Range>)
    -> custom_take_view<std::ranges::views::all_t<Range>>;

// range adapter
template <std::integral T>
struct custom_take_range_adaptor_closure {
    T mCount;

    explicit constexpr custom_take_range_adaptor_closure(T count)
        : mCount{ count }
    {
    }

    template <std::ranges::viewable_range Range>
    constexpr auto operator()(Range&& range) const
    {
        return custom_take_view(std::forward<Range>(range), mCount);
    }
};

struct custom_take_range_adaptor {
    template <typename... Args>
    constexpr auto operator()(Args&&... args)
    {
        if constexpr (sizeof...(Args) == 1) {
            return custom_take_range_adaptor_closure{ args... };
        } else {
            return custom_take_view{ std::forward<Args>(args)... };
        }
    }
};

template <std::ranges::viewable_range Range, typename T>
constexpr auto operator|(Range&& range, custom_take_range_adaptor_closure<T> const& adaptor)
{
    return adaptor(std::forward<Range>(range));
}

namespace views
{
inline custom_take_range_adaptor custom_take;
}

int main()
{
    auto is_even = [](auto const& element) { return element % 2 == 0; };

    std::vector<int> const v{ 1, 2, 3, 4, 5, 6, 7, 8 };
    auto result = v | std::ranges::views::filter(is_even) | views::custom_take(2);

    for (auto const& element : result) {
        spdlog::info("{}", element);
    }

    return EXIT_SUCCESS;
}
