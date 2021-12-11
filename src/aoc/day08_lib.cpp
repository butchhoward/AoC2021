#include "aoc/day08_lib.h"
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
using namespace day08lib;

namespace {

typedef const std::map<int, std::string> NormalSignalInfo;
NormalSignalInfo normal_signals{
    {0,"abcefg"},
    {1,"cf"},
    {2,"acedg"},
    {3,"acdfg"},
    {4,"bcdf"},
    {5,"abdfg"},
    {6,"abdefg"},
    {7,"acf"},
    {8,"abdcefg"},
    {9,"abcdfg"}
};

typedef struct DigitalDisplay
{
    std::vector<std::string> inputs;
    std::vector<std::string> outputs;

} Thing;
typedef std::vector<DigitalDisplay> DigitalDisplays;

std::ostream & operator<<(std::ostream &os, const std::vector<std::string>& things)
{
    for (auto thing : things)
    {
        os << "'" << thing << "' ";
    }

    return os;
}

std::ostream & operator<<(std::ostream &os, const DigitalDisplay& thing)
{
    os << "INPUTS : " << thing.inputs << std::endl
       << "OUTPUTS: " << thing.outputs << std::endl
       ;
    return os;
}

#pragma GCC diagnostic ignored "-Wunused-function"
std::ostream & operator<<(std::ostream &os, const DigitalDisplays& things)
{
    for (auto thing : things)
    {
        os << thing << std::endl;
    }
    return os;
}


//from: https://stackoverflow.com/a/217605
// trim from start (in place)
inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

// trim from start (copying)
inline std::string ltrim_copy(std::string s) {
    ltrim(s);
    return s;
}

// trim from end (copying)
inline std::string rtrim_copy(std::string s) {
    rtrim(s);
    return s;
}

// trim from both ends (copying)
inline std::string trim_copy(std::string s) {
    trim(s);
    return s;
}

DigitalDisplays parse_datastream(std::istream& data_stream)
{
    DigitalDisplays data;

    std::string line;
    for (;std::getline(data_stream, line);)
    {
        DigitalDisplay display;

        auto parts = parser_helpers::split(line, '|');
        display.inputs = parser_helpers::split(trim_copy(parts[0]));
        display.outputs = parser_helpers::split(trim_copy(parts[1]));

        data.push_back(display);
    }

    return data;
}

}

std::size_t day08lib::part1_solve(std::istream& data_stream)
{
    auto displays = parse_datastream(data_stream);

    std::vector<size_t> special_lengths{
        normal_signals.at(1).length(),
        normal_signals.at(4).length(),
        normal_signals.at(7).length(),
        normal_signals.at(8).length()
    };

    auto count_special_signals_in_an_output = [&](auto t, const auto& o)
                                {
                                    return t += (special_lengths.cend() != std::find(
                                            special_lengths.cbegin(),
                                            special_lengths.cend(),
                                            o.length())) ? 1 : 0;
                                };

    auto count_special_signals_in_outputs = [&](auto t, const auto& d)
                                {
                                    return t + std::accumulate(d.outputs.cbegin(), d.outputs.cend(), 0,
                                                count_special_signals_in_an_output
                                    );
                                };


    auto ds = std::accumulate( displays.cbegin(), displays.cend(), 0,
                                    count_special_signals_in_outputs );

    return ds;
}

std::size_t day08lib::part2_solve(std::istream& data_stream)
{
    auto things = parse_datastream(data_stream);
    return 0;
}
