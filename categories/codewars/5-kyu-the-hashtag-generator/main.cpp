#include <cstdlib>
#include <optional>
#include <spdlog/spdlog.h>
#include <string>

/*
The marketing team is spending way too much time typing in hashtags.
Let's help them with our own Hashtag Generator!

Here's the deal:

    It must start with a hashtag (#).
    All words must have their first letter capitalized, and remaining letters lowercased.

    If the final result is longer than 140 chars it must return std::nullopt.
    If the input or the result is an empty string it must return std::nullopt.

Examples

" Hello there thanks for trying my Kata"  =>  "#HelloThereThanksForTryingMyKata"
"    Hello     World   "                  =>  "#HelloWorld"
""                                        =>  std::nullopt

 */

using str_t = std::string;
using opt_str_t = std::optional<str_t>;

opt_str_t generate_hashtag(const str_t& str)
{
    if (str.empty()) {
        return std::nullopt;
    }

    std::string result{ "#" };

    bool wordFound{ true };
    for (std::size_t i = 0; i < str.size(); ++i) {
        if (str[i] == ' ') {
            wordFound = true;
            continue;
        }

        if (wordFound) {
            result += std::toupper(str[i]);
            wordFound = false;
        } else {
            result += std::tolower(str[i]);
        }

        if (result.size() > 140) {
            return std::nullopt;
        }
    }

    if (result == "#") {
        return std::nullopt;
    }

    return result;
}

int main()
{
    auto const r1 = generate_hashtag("Hello WoRlD Lalala");
    auto const r2 = generate_hashtag("");
    auto const r3 = generate_hashtag("code" + std::string(149, ' ') + "wars");

    if (r1) {
        spdlog::info("{}", *r1);
    }

    if (!r2) {
        spdlog::info("invalid input");
    }

    if (r3) {
        spdlog::info("{}", *r3);
    }

    return EXIT_SUCCESS;
}
