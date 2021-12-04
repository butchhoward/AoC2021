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
#include <ranges>

using namespace day2lib;

namespace {

typedef enum {
    HALT,
    FORWARD,
    BACK,
    UP,
    DOWN,
    PORT,
    STARBOARD
} Direction;

std::map<std::string, Direction> DirectionName = {
     {"HALT",HALT}
    ,{"FORWARD", FORWARD}
    ,{"BACK", BACK}
    ,{"UP", UP}
    ,{"DOWN", DOWN}
    ,{"PORT", PORT}
    ,{"STARBOARD", STARBOARD}
};

typedef struct NavCommand
{
    NavCommand():
        name("HALT"), direction(DirectionName[name]), distance(0)
    {
    }

    NavCommand(std::string c, int d):
        name(c), direction(DirectionName[name]), distance(d)
    {
    }

    std::string name;
    Direction direction;
    int distance;
} NavCommand;
typedef std::vector<NavCommand> NavCommands;



//from https://www.fluentcpp.com/2019/05/14/3-types-of-macros-that-improve-c-code/
#define FWD(...) ::std::forward<decltype(__VA_ARGS__)>(__VA_ARGS__)


NavCommand parse_data_line( const std::string& pp )
{
    //this was a deep c++20 hole I fell into...lots of learning here

    //from https://brevzin.github.io/c++/2020/07/06/split-view/
    auto split_strs = [](auto&& pattern){
        return std::ranges::views::split(FWD(pattern))
            | std::ranges::views::transform([](auto p){
                auto c = p | std::ranges::views::common;
                return std::string(c.begin(), c.end());
            });
    };

    auto fields = pp | split_strs(' ');
    auto fields_as_vector = std::vector<std::string>(fields.begin(), fields.end());

    int distance{0};
    std::istringstream s_value(fields_as_vector[1]);
    s_value >> distance;

    return NavCommand(fields_as_vector[0], distance);
}


NavCommands parse_datastream(std::istream& data_stream)
{

     NavCommands commands;

    std::string line;
    for (;std::getline(data_stream, line);)
    {   
        commands.push_back(parse_data_line(line));
    }
    
    return commands;
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
