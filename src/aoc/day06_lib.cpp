#include "aoc/day06_lib.h"

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

typedef struct Fish
{
    Fish() : timer(-1)
    {
    }
    Fish(int d) : timer(d)
    {
    }

    int timer;
} Fish;

typedef std::vector<Fish> Fishes;

std::ostream & operator<<(std::ostream &os, const Fish& fish)
{
    os << fish.timer;
    return os;
}

#pragma GCC diagnostic ignored "-Wunused-function"
std::ostream & operator<<(std::ostream &os, const Fishes& fishes)
{
    for (auto fish : fishes)
    {
        os << fish << ",";
    }
    os << std::endl;
    return os;
}

Fishes parse_datastream(std::istream& data_stream)
{
    Fishes data;

    std::string line;
    for (;std::getline(data_stream, line);)
    {
        std::istringstream timers(line);
        for(;;)
        {
            if (timers.eof())
            {
                break;
            }
            Fish fish;
            timers >> fish.timer;
            timers.ignore(std::numeric_limits<std::streamsize>::max(), ',');
            data.push_back(fish);
        }
    }

    return data;
}

Fishes update_spawn(Fishes& fishes)
{
    Fishes new_fishes;
    const int default_timer{6};
    const int new_fish_bonus{2};

    for (auto &fish : fishes)
    {
        if (fish.timer == 0)
        {
            fish.timer = 6;
            new_fishes.push_back( Fish(default_timer + new_fish_bonus) );
        }
        else
        {
            --fish.timer;
        }
    }

    return new_fishes;

}

void model_spawn(Fishes& fishes, int days)
{

    std::cout << "MODEL" << std::endl;

    for (auto day=0; day < days; ++day)
    {
        Fishes new_fishes;

        std::cout << "+" << std::flush;
        new_fishes = update_spawn(fishes);

        fishes.insert( fishes.end(), new_fishes.begin(), new_fishes.end());
        std::cout << day << "(" << fishes.size() << ") ";
    }
    std::cout << std::endl;

}

}

std::size_t day06lib::part1_solve(std::istream& data_stream, int days)
{
    auto fishes = parse_datastream(data_stream);
    std::cout << "input size:" << fishes.size() << std::endl;

    model_spawn(fishes, days);

    return fishes.size();
}

std::size_t day06lib::part2_solve(std::istream& data_stream, int days)
{
    return part1_solve(data_stream, days);
}
