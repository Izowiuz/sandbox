#include <concepts>
#include <cstdlib>
#include <iostream>
#include <string>
#include <type_traits>
#include <utility>

#include "spdlog/spdlog.h"

auto const l1 = []<typename T>(T const& a, T const& b) { spdlog::info("a: {}, b: {}", a, b); };

// single prefix print
template <typename Prefix, typename... Ts>
void print(Prefix&& prefix, Ts&&... args)
{
    std::cout << "[ " << std::forward<Prefix>(prefix) << " ]";
    (..., ((std::cout << " " << std::forward<Ts>(args))));
    std::cout << "\n";
}

// multiple prefix print
template <typename Prefix, typename... Ts>
void print_multiple(Prefix&& prefix, Ts const&... args)
{
    std::cout << "[ " << std::forward<Prefix>(prefix) << " ]";
    (..., (std::cout << " " << args));
    std::cout << "\n";
}

// single prefix "printer getter"
auto l2(std::string const& prefix)
{
    return [=]<typename... Ts>(Ts... args) { print(prefix, std::forward<Ts>(args)...); };
};

// multiple prefix "printer getter"
template <typename... Prefixes>
auto l3(Prefixes&&... prefixes)
{
    return [... _prefixes = std::forward<Prefixes>(prefixes)]<typename... Ts>(Ts... args)
        requires(not std::disjunction_v<std::is_pointer<Prefixes>...>)
    { print(_prefixes..., std::forward<Ts>(args)...); };
};

int main()
{
    l1(1, 2);
    // will not compile - different types are not permited on a template level:
    // l1(1, 2.0F);

    // single prefixes
    print("a", 1, 3.8F, 3);
    l2("b")(1, 3.8F, 3);

    // multiple prefixes
    print_multiple("a", "b", 1, 2, 3);
    l3("a", "b")(1, 2, 3);

    // will not compile - prefixes cannot be pointers
    // std::string a = "lalala";
    // l3("a", "b", &a)(1, 2, 3);

    return EXIT_SUCCESS;
}
