#include <vector>
#include <string>
#include <sstream>

#include <fmt/ranges.h>
#include <spdlog/spdlog.h>

/*
Write a function to split a string and convert it into an array of words.
Examples (Input ==> Output):

"Robin Singh" ==> ["Robin", "Singh"]

"I love arrays they are my favorite" ==> ["I", "love", "arrays", "they", "are", "my", "favorite"]
*/

std::vector<std::string> string_to_array(const std::string& s) {
    if (s.empty()) {
        return {""};
    }

    std::vector<std::string> ret;
    std::stringstream ss(s);

    std::string word;
    while(ss >> word) {
        ret.push_back(word);
    }

    return ret;
}

int main()
{
    spdlog::info(string_to_array("Robin Singh"));

    return EXIT_SUCCESS;
}
