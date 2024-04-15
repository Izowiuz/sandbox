#include <cstdlib>
#include <string>
#include <type_traits>

#include "spdlog/spdlog.h"

class foo
{
};

template <typename T, typename... Ts>
constexpr inline bool are_same_v = std::conjunction_v<std::is_same<T, Ts>...>;

// first arg - the classic approach
template <typename T, typename...>
struct first_arg {
    using type = T;
};

// first arg - the tuple approach
template <typename... Args>
struct first_arg_v2 {
    using type = typename std::tuple_element<0, std::tuple<Args...>>::type;
};

template <typename... Args>
using first_arg_t = typename first_arg<Args...>::type;

template <typename... Args>
using first_arg_t_v2 = typename first_arg_v2<Args...>::type;

// pre concepts
template <typename... Args>
std::enable_if_t<are_same_v<Args...>, first_arg_t<Args...>> add(Args const&... args) noexcept
{
    return (... + args);
}

// post concepts
template <typename... Args>
    requires are_same_v<Args...>
auto add_v2(Args const&... args) noexcept
{
    return (... + args);
}

// concept definition

template <typename... Args>
concept Addable = requires(Args... args) {
    (... + args);
    requires are_same_v<Args...>;
    requires sizeof...(Args) > 1;
    { (... + args) } noexcept -> std::same_as<first_arg_t_v2<Args...>>;
};

// post concepts - with concept defined
template <typename... Args>
    requires Addable<Args...>
auto add_v3(Args const&... args) noexcept
{
    return (... + args);
}

int main()
{
    spdlog::info("first_arg_t: {}", typeid(first_arg_t<int, float, bool>).name());
    spdlog::info("first_arg_t: {}", typeid(first_arg_t<std::string, float, bool>).name());
    spdlog::info("first_arg_t: {}", typeid(first_arg_t<foo, float, bool>).name());

    spdlog::info("first_arg_t_v2: {}", typeid(first_arg_t_v2<int, float, bool>).name());
    spdlog::info("first_arg_t_v2: {}", typeid(first_arg_t_v2<std::string, float, bool>).name());
    spdlog::info("first_arg_t_v2: {}", typeid(first_arg_t_v2<foo, float, bool>).name());

    spdlog::info("add: {}", add(1, 2, 42));
    spdlog::info("add: {}", add(1));
    spdlog::info("add: {}", add(std::string("1"), std::string("2"), std::string("42")));
    // does not compile
    // spdlog::info("add: {}", add(1, 2.f, 42));

    spdlog::info("add_v2: {}", add_v2(1, 2, 42));
    spdlog::info("add_v2: {}", add_v2(1));
    spdlog::info("add_v2: {}", add_v2(std::string("1"), std::string("2"), std::string("42")));
    // does not compile
    // spdlog::info("add_v2: {}", add_v2(1, 2.f, 42));

    spdlog::info("add_v3: {}", add_v3(1, 2, 42));
    // spdlog::info("add: {}", add_v3(1, 2.f, 42));
    // spdlog::info("add_v3: {}", add_v3(std::string("1"), std::string("2"), std::string("42")));
    // spdlog::info("add_v2: {}", add_v3(1));

    return EXIT_SUCCESS;
}
