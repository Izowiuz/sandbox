#include <cmath>
#include <cstdlib>
#include <spdlog/spdlog.h>

/*
Introduction

The first century spans from the year 1 up to and including the year 100, the second century - from
the year 101 up to and including the year 200, etc. Task

Given a year, return the century it is in.
Examples

1705 --> 18
1900 --> 19
1601 --> 17
2000 --> 20
2742 --> 28

Note: this kata uses strict construction as shown in the description and the examples, you can read
more about it here

*/

int centuryFromYear(int year)
{
    return std::ceil(static_cast<float>(year) / 100);
}

int main()
{
    spdlog::info(centuryFromYear(1705));

    return EXIT_SUCCESS;
}
