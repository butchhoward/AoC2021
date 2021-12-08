#include "aoc/day05_lib.h"

#include <iostream>
#include <sstream>
#include <cstddef>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <functional>

using namespace day05lib;

namespace {

typedef int Thing;
typedef std::vector<Thing> Things;

Things parse_datastream(std::istream& data_stream)
{
    Things data;

    std::string line;
    for (;std::getline(data_stream, line);)
    {
        std::istringstream v(line);
    }

    return data;
}

}

std::size_t day05lib::part1_solve(std::istream& data_stream)
{
    auto things = parse_datastream(data_stream);
    return 0;
}

std::size_t day05lib::part2_solve(std::istream& data_stream)
{
    auto things = parse_datastream(data_stream);
    return 0;
}