#include "aoc/day2_lib.h"

#include <iostream>
#include <sstream>
#include <cstddef>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <functional>

using namespace day2lib;

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

std::size_t day2lib::part1_solve(std::istream& data_stream)
{
    auto things = parse_datastream(data_stream);
    return 0;
}

std::size_t day2lib::part2_solve(std::istream& data_stream)
{
    auto things = parse_datastream(data_stream);
    return 0;
}
