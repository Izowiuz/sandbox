#include <cstdlib>
#include <unordered_map>

#include <spdlog/spdlog.h>

template <typename Key, typename Value>
void insert(std::unordered_map<Key, Value>& map, Key const& key, Value const& value)
{
    if (auto const [it, flag] = map.insert({ key, value }); flag) {
        spdlog::info("inserted! [{}, {}]", key, value);
    } else {
        spdlog::info("not inserted! [{}, {}]", key, value);
    }
}

int main()
{
    std::unordered_map<std::int32_t, std::int32_t> map;

    insert(map, 1, 1);
    insert(map, 2, 2);
    insert(map, 2, 3);

    return EXIT_SUCCESS;
}
