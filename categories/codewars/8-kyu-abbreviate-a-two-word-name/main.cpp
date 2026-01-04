#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <spdlog/spdlog.h>
#include <string>

/*
Write a function to convert a name into initials. This kata strictly takes two words with one space
in between them.

The output should be two capital letters with a dot separating them.

It should look like this:

Sam Harris => S.H

patrick feeney => P.F
*/

std::string abbrevName_1(std::string name)
{
    if (name.empty()) {
        return "";
    }

    auto tmp = std::move(name);
    std::string ret;

    ret += tmp[0];

    auto const spacePosition = tmp.find_first_of(" ");
    if (spacePosition < name.size() - 1) {
        ret += ".";
        ret += tmp[spacePosition + 1];
    }

    return ret;
}

std::string abbrevName_2(std::string name)
{
    if (name.empty()) {
        return "";
    }

    auto tmp = std::move(name);
    std::string ret;
    unsigned char lastChar = '.';

    for (auto const& c : tmp) {
        if (c == ' ') {
            ret += '.';
            lastChar = '.';
        } else if (lastChar == '.') {
            ret += c;
            lastChar = c;
        }
    }

    return ret;
}

std::string abbrevName_3(std::string name)
{
    if (name.empty()) {
        return "";
    }

    auto tmp = std::move(name);
    std::size_t nextPeriodPosition = 1;
    bool foundSpace = false;

    tmp[0] = std::toupper(static_cast<unsigned char>(tmp[0]));

    for (std::size_t i = 0; i < tmp.size();) {
        if (foundSpace) {
            tmp[nextPeriodPosition - 1] = std::toupper(static_cast<unsigned char>(tmp[i]));
            foundSpace = false;
        }

        if (tmp[i] == ' ' && nextPeriodPosition < tmp.size()) {
            tmp[nextPeriodPosition] = '.';
            nextPeriodPosition += 2;
            foundSpace = true;
        }
        ++i;
    }

    tmp.resize(nextPeriodPosition);
    return tmp;
}

int main()
{
    spdlog::info(abbrevName_1("Some One"));
    spdlog::info(abbrevName_2("Some One"));
    spdlog::info(abbrevName_3("some one Now"));
    spdlog::info(abbrevName_3("Some"));

    return EXIT_SUCCESS;
}
