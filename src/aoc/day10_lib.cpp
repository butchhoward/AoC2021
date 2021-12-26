#include "aoc/day10_lib.h"
#include "library/stream_helpers.h"

#include <iostream>
#include <sstream>
#include <cstddef>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <functional>
#include <stack>

using namespace day10lib;


namespace {

}


#pragma GCC diagnostic ignored "-Wunused-function"
std::ostream & day10lib::operator<<(std::ostream &os, const NavSystem& things)
{
    for (auto thing : things)
    {
        os << "'" << thing << "' ";
    }

    return os;
}


std::tuple<bool, char> day10lib::validate_nav_line(const NavLine& nav_line)
{

    std::map<char,char> marker_starts
    {
        {'(',')'},
        {'[',']'},
        {'{','}'},
        {'<','>'}
    };

    std::map<char,char> marker_ends
    {
        {')','('},
        {']','['},
        {'}','{'},
        {'>','<'}
    };

    std::istringstream v(nav_line);

    std::stack<char> chunk_ends;


    while( true )
    {
        char c;
        v >> c;

        if ( v.eof() )
            break;

        if (marker_starts.contains(c))
        {
            chunk_ends.push(c);
            continue;
        }

        auto expected_start = marker_ends.at(c);

        if ( expected_start != chunk_ends.top() )
        {
            return std::tuple<bool, char>(false, c);   
        }

        chunk_ends.pop();
    }

    return std::tuple<bool, char>(true, '\0');
}

NavSystem day10lib::parse_datastream(std::istream& data_stream)
{
    NavSystem nav_system;

    std::string line;
    for (;std::getline(data_stream, line);)
    {
        nav_system.push_back(line);
    }

    return nav_system;
}

std::size_t day10lib::part1_solve(std::istream& data_stream)
{
    auto nav_system = parse_datastream(data_stream);

    std::map<char, int> scores
    {
        {')',3},
        {']',57},
        {'}',1197},
        {'>',25137}    
    };


    return std::accumulate( nav_system.cbegin(), nav_system.cend(), 0,
                            [&scores](auto t, const NavLine& n)
                            {
                                auto [v,c] = validate_nav_line(n);
                                if (v)
                                {
                                    return t;
                                }
                                return t + scores.at(c);
                            }
    );
}

std::size_t day10lib::part2_solve(std::istream& data_stream)
{
    auto nav_system = parse_datastream(data_stream);
    return 0;
}
