#include <cstdlib>
#include <map>
#include <string>
#include <utility>

#include <spdlog/spdlog.h>

struct Element {
    std::string name;
};

struct ElementValue {
    int value{ 0 };
};

// we can use 'using' to define a type to use it later
// this is a lambda in unevaluated context
// only captureless lambdas work that way
using comparator = decltype([](auto const& lhs, auto const& rhs) { return lhs.name < rhs.name; });

template <typename Value>
using MapElementsSortedByName = std::map<Element, Value, comparator>;

int main()
{
    // here we allow std::map to default construct comparator lambda
    MapElementsSortedByName<ElementValue> map;
    map.insert(std::make_pair(Element{ "x" }, ElementValue{ 1 }));
    map.insert(std::make_pair(Element{ "c" }, ElementValue{ 2 }));
    map.insert(std::make_pair(Element{ "b" }, ElementValue{ 123 }));
    map.insert(std::make_pair(Element{ "n" }, ElementValue{ 42 }));
    map.insert(std::make_pair(Element{ "a" }, ElementValue{ 22 }));

    for (auto const& [element, value] : map) {
        spdlog::info("element name: {}, element value: {}", element.name, value.value);
    }

    return EXIT_SUCCESS;
}
