#include "aoc/day09_lib.h"

#include <iostream>
#include <sstream>
#include <cstddef>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <functional>

using namespace day09lib;

namespace {

typedef struct Thing
{
    int value;
} Thing;
typedef std::vector<Thing> Things;

std::ostream & operator<<(std::ostream &os, const Thing& thing)
{
    os << thing.value;
    return os;
}

#pragma GCC diagnostic ignored "-Wunused-function"
std::ostream & operator<<(std::ostream &os, const Things& things)
{
    for (auto thing : things)
    {
        os << thing << std::endl;
    }
    return os;
}

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

std::size_t day09lib::part1_solve(std::istream& data_stream)
{
    auto things = parse_datastream(data_stream);
    std::cout << things << std::endl;
    return 0;
}

std::size_t day09lib::part2_solve(std::istream& data_stream)
{
    auto things = parse_datastream(data_stream);
    return 0;
}
