#include "aoc/day02_lib.h"
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
#include <ranges>

using namespace day02lib;

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
     {"halt",HALT}
    ,{"forward", FORWARD}
    ,{"back", BACK}
    ,{"up", UP}
    ,{"down", DOWN}
    ,{"port", PORT}
    ,{"starboard", STARBOARD}
};

typedef struct NavCommand
{
    NavCommand():
        name("HALT"), direction(DirectionName[name]), value(0)
    {
    }

    NavCommand(std::string c, int d):
        name(c), direction(DirectionName[name]), value(d)
    {
    }

    std::string name;
    Direction direction;
    int value;
} NavCommand;
typedef std::vector<NavCommand> NavCommands;

// std::ostream & operator<<(std::ostream &os, const NavCommands& ps);
// std::ostream & operator<<(std::ostream &os, const NavCommand& p);

// std::ostream & operator<<(std::ostream &os, const NavCommands& ns)
// {
//     for ( auto n : ns)
//     {
//         os << n << std::endl;
//     }
//     return os;
// }

// std::ostream & operator<<(std::ostream &os, const NavCommand& n)
// {

//     os << n.name
//        << ":"
//        << n.value
//        ;

//     return os;
// }



NavCommand parse_data_line( const std::string& pp )
{
    auto fields_as_vector = parser_helpers::split(pp);

    int value{0};
    std::istringstream s_value(fields_as_vector[1]);
    s_value >> value;

    return NavCommand(fields_as_vector[0], value);
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

std::size_t day02lib::part1_solve(std::istream& data_stream)
{
    auto commands = parse_datastream(data_stream);

    // std::cout << commands << std::endl;

    int vertical{0};
    int horizontal{0};
    for ( auto c : commands )
    {
        switch (c.direction) {
        case Direction::FORWARD: horizontal += c.value; break;

        case Direction::UP: vertical -= c.value; break;
        case Direction::DOWN: vertical += c.value; break;

        case Direction::BACK:
        case Direction::PORT:
        case Direction::STARBOARD:
        case Direction::HALT:
        default:
            std::cout << "Not handled: ";
            break;
        }

        // std::cout << c << ", " << vertical << ", " << horizontal << std::endl;
    }

    return vertical * horizontal;
}

std::size_t day02lib::part2_solve(std::istream& data_stream)
{
    auto commands = parse_datastream(data_stream);

    // std::cout << commands << std::endl;

    int vertical{0};
    int horizontal{0};
    int aim{0};
    for ( auto c : commands )
    {
        switch (c.direction) {
        case Direction::FORWARD:
        {
            horizontal += c.value;
            vertical += c.value * aim;
            break;
        }

        case Direction::UP: aim -= c.value; break;
        case Direction::DOWN: aim += c.value; break;

        case Direction::BACK:
        case Direction::PORT:
        case Direction::STARBOARD:
        case Direction::HALT:
        default:
            std::cout << "Not handled: ";
            break;
        }

        // std::cout << c << ", " << vertical << ", " << horizontal << std::endl;
    }

    return vertical * horizontal;
}
