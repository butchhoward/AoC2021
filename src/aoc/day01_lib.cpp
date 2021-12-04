#include <aoc/day01_lib.h>

#include <climits>
#include <iostream>
#include <sstream>
#include <cstddef>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <functional>

using namespace day01lib;

namespace {

typedef int SonarDepth;
typedef std::vector<SonarDepth> SonarDepths;

SonarDepths parse_datastream(std::istream& data_stream)
{
    SonarDepths depths;

    std::string line;
    for (;std::getline(data_stream, line);)
    {
        int depth{0};
        std::istringstream s_value(line);
        s_value >> depth;
        depths.push_back(depth);
    }

    return depths;
}

}


std::size_t day01lib::part1_solve(std::istream& data_stream)
{
    auto depths = parse_datastream(data_stream);

    int count{0};
    int last{0};
    bool first{true};
    for (auto depth : depths)
    {
        if (first)
        {
            last = depth;
            first = false;
            continue;
        }

        if (depth > last)
        {
            ++count;
        }
        last = depth;
    }
    return count;
}

std::size_t day01lib::part2_solve(std::istream& data_stream)
{
    auto depths = parse_datastream(data_stream);
    int count{0};
    int last{INT_MAX};

    for ( std::size_t index=0; index < depths.size(); ++index )
    {
        int current{0};
        for (auto window = index; window < depths.size() && window < index + 3; ++window)
        {
            current += depths[window];
        }

        if (current > last)
        {
            ++count;
        }

        last = current;
    }

    return count;
}
