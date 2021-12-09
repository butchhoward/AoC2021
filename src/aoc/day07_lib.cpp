#include "aoc/day07_lib.h"
#include <library/parser_helpers.h>

#include <iostream>
#include <sstream>
#include <cstddef>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <functional>

using namespace day07lib;

namespace {

typedef std::pair<int, int> CrabPosition;
typedef std::map<size_t, int> CrabPositions;

#pragma GCC diagnostic ignored "-Wunused-function"
std::ostream & operator<<(std::ostream &os, const CrabPosition& p)
{
    os << p.first << ":" << p.second;
    return os;
}

#pragma GCC diagnostic ignored "-Wunused-function"
std::ostream & operator<<(std::ostream &os, const CrabPositions& ps)
{
    for (auto& [p,v] : ps)
    {
        os << p <<":[" << v << "] ";
    }
    os << std::endl;
    return os;
}

CrabPositions parse_datastream(std::istream& data_stream)
{
    CrabPositions crab_positions;

    auto positions = parser_helpers::parse_comma_ints(data_stream);

    for (auto p : positions)
    {
        crab_positions.try_emplace(p, 0);
        crab_positions.insert_or_assign(p, crab_positions[p]+1);
    }

    return crab_positions;
}

size_t max_position(const CrabPositions& crab_positions)
{
    size_t the_max{0};
    for ( auto& [p,c] : crab_positions)
    {
        the_max = std::max(the_max, p);
    }
    return the_max;
}

typedef size_t(*CrabEnergyFunction)(const CrabPositions& crab_positions, size_t pos);

size_t cost_to_move_all_increasing(const CrabPositions& crab_positions, size_t pos)
{
    auto move_cost = [](size_t from, size_t to)
    {
        size_t c{0};
        for (auto x=std::min(from,to); x <= std::max(from,to); ++x)
        {
            c += abs(x-to);
        }
        return c;
    };

    return std::accumulate(crab_positions.begin(), crab_positions.end(), (size_t)0,
                            [pos,move_cost](auto t, const auto p)
                            {
                                return t + move_cost(p.first, pos) * p.second;
                            }
                        );
}

size_t cost_to_move_all_const(const CrabPositions& crab_positions, size_t pos)
{
    return std::accumulate(crab_positions.begin(), crab_positions.end(), (size_t)0,
                            [pos](auto t, const auto p)
                            {
                                return t + abs(p.first-pos) * p.second;
                            }
                        );
}

size_t minimum_energy_move(const CrabPositions& crab_positions, CrabEnergyFunction energy_function)
{
    auto max_pos = max_position(crab_positions);

    size_t min_energy=std::numeric_limits<size_t>::max();

    for (size_t pos=0; pos<=max_pos; ++pos)
    {
        min_energy = std::min(min_energy, energy_function(crab_positions, pos));
    }

    return min_energy;
}

}

std::size_t day07lib::part1_solve(std::istream& data_stream)
{
    auto crab_positions = parse_datastream(data_stream);
    return minimum_energy_move(crab_positions, cost_to_move_all_const);
}

std::size_t day07lib::part2_solve(std::istream& data_stream)
{
    auto crab_positions = parse_datastream(data_stream);
    return minimum_energy_move(crab_positions, cost_to_move_all_increasing);
}
