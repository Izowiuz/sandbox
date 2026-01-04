#include <algorithm>
#include <cstdlib>
#include <spdlog/spdlog.h>
#include <string>
#include <vector>

/*
Can you find the needle in the haystack?

Write a function findNeedle() that takes an array full of junk but containing one "needle"

After your function finds the needle it should return a message (as a string) that says:

"found the needle at position " plus the index it found the needle, so:

Example(Input --> Output)

["hay", "junk", "hay", "hay", "moreJunk", "needle", "randomJunk"] --> "found the needle at position
5"

Note: In COBOL, it should return "found the needle at position 6"
*/

std::string findNeedle(const std::vector<std::string>& haystack)
{
    auto const it = std::find(haystack.begin(), haystack.end(), "needle");
    if (it == haystack.end()) {
        return "failed to find needle";
    }

    auto const needlePosition = std::distance(haystack.begin(), it);
    return "found the needle at position " + std::to_string(needlePosition);
}

int main()
{
    spdlog::info(findNeedle({ "hay", "junk", "hay", "hay", "moreJunk", "needle", "randomJunk" }));

    return EXIT_SUCCESS;
}
