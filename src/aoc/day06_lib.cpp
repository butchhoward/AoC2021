#include "aoc/day06_lib.h"
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

using namespace day06lib;

namespace {

typedef unsigned long long FishCounter;

typedef struct FishDay
{
    FishDay() : fish(0)
    {
    }
    FishDay(FishCounter f) : fish(f)
    {
    }

    FishCounter fish;
} FishDay;

typedef std::vector<FishDay> FishDays;

std::ostream & operator<<(std::ostream &os, const FishDay& day)
{
    os << day.fish;
    return os;
}

#pragma GCC diagnostic ignored "-Wunused-function"
std::ostream & operator<<(std::ostream &os, const FishDays& days)
{
    int counter{0};
    for (auto day : days)
    {
        os << counter++ << "(" << day << ")" << " ";
    }
    os << std::endl;
    return os;
}

FishDays parse_datastream(std::istream& data_stream)
{

    auto fish_timers = parser_helpers::parse_comma_ints(data_stream);

    FishDays fishdays(9);

    for (auto fish_timer : fish_timers)
    {
        fishdays[fish_timer].fish++;
    }

    return fishdays;
}

FishDays update_spawn(const FishDays& fishdays)
{
    FishDays updated_fishdays(fishdays);
    const size_t after_spawn_bucket = 6;
    const size_t new_fish_bucket = 8;

    auto new_fish = updated_fishdays[0].fish;

    for(size_t bucket=0; bucket < updated_fishdays.size()-1; ++bucket )
    {
        updated_fishdays[bucket].fish = updated_fishdays[bucket+1].fish;
    }
    updated_fishdays[new_fish_bucket].fish = new_fish;
    updated_fishdays[after_spawn_bucket].fish = updated_fishdays[after_spawn_bucket].fish + new_fish;

    return updated_fishdays;

}

FishDays model_spawn(const FishDays& initial_fishdays, int days)
{

    FishDays fishdays(initial_fishdays);

    for (auto day=0; day < days; ++day)
    {
        fishdays = update_spawn(fishdays);
    }

    return fishdays;
}

}

std::size_t day06lib::part1_solve(std::istream& data_stream, int days)
{
    auto fishdays = parse_datastream(data_stream);

    fishdays = model_spawn(fishdays, days);

    return std::accumulate(fishdays.begin(), fishdays.end(), (FishCounter)0,
                                        [](auto t, const FishDay& d){ return t + d.fish;}
                                    );
}

std::size_t day06lib::part2_solve(std::istream& data_stream, int days)
{
    return part1_solve(data_stream, days);
}
