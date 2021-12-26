#include "aoc/day08_lib.h"
#include <library/parser_helpers.h>
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
#include <ranges>
using namespace day08lib;

std::ostream & day08lib::operator<<(std::ostream &os, const std::vector<std::string>& things)
{
    for (auto thing : things)
    {
        os << "'" << thing << "' ";
    }

    return os;
}

std::ostream & day08lib::operator<<(std::ostream &os, const DigitalDisplay& thing)
{
    os << "INPUTS : " << thing.inputs << std::endl
       << "OUTPUTS: " << thing.outputs << std::endl
       ;
    return os;
}

#pragma GCC diagnostic ignored "-Wunused-function"
std::ostream & day08lib::operator<<(std::ostream &os, const DigitalDisplays& things)
{
    for (auto thing : things)
    {
        os << thing << std::endl;
    }
    return os;
}

std::ostream & day08lib::operator<<(std::ostream &os, const Decoder& decoder)
{
    for (auto& [k,v]: decoder)
    {
        os << k << ":" << v << ", ";
    }
    return os;
}


namespace {

typedef const std::map<int, std::string> NormalSignalInfo;
NormalSignalInfo normal_signals{
    {0,"abcefg"},
    {1,"cf"},
    {2,"acdeg"},
    {3,"acdfg"},
    {4,"bcdf"},
    {5,"abdfg"},
    {6,"abdefg"},
    {7,"acf"},
    {8,"abcdefg"},
    {9,"abcdfg"}
};



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

}

Decoder day08lib::create_decoder(const day08lib::DigitalDisplay& display)
{
    Decoder decoded_signals;

    auto find_all_lenX = [](std::vector<std::string> inputs, size_t lenX)
                     {
                         std::vector<std::string> inputs_lenX;
                         for (auto i = inputs.cbegin(); i != inputs.cend(); ++i)
                         {
                             if (i->length() == lenX)
                             {
                                 inputs_lenX.push_back(*i);
                             }
                         }
                         return inputs_lenX;
                     };

    auto find_lenX = [](std::vector<std::string> inputs, size_t lenX)
                     {
                         std::vector<std::string> inputs_lenX;
                         for (auto i = inputs.cbegin(); i != inputs.cend(); ++i)
                         {
                             if (i->length() == lenX)
                             {
                                return  *i;
                            }
                         }

                         return std::string();
                     };

    auto diff = [](const std::string lhs, const std::string rhs)
                {
                    std::string d(lhs);
                    for (auto c : rhs)
                    {
                        auto f = d.find(c);
                        if (f != std::string::npos)
                        {
                            d.erase(f, 1);
                        }
                    }

                    return d;
                };

    auto union_of = [](const std::string lhs, const std::string rhs)
                {
                    std::string u(lhs);
                    for (auto c : rhs)
                    {
                        auto f = u.find(c);
                        if (f == std::string::npos)
                        {
                            u.push_back(c);
                        }
                    }
                    return u;
                };

    auto STRC = [](char c) { return std::string(1,c); };

    auto sub_from_all = [diff](std::vector<std::string> inputs, std::string rhs)
                        {
                            std::vector<std::string> results;
                            for ( auto s : inputs)
                            {
                                results.push_back(diff(s, rhs));
                            }
                            return results;
                        };


    // 3-2=a
    auto input3 = find_lenX(display.inputs, 3);
    auto input2 = find_lenX(display.inputs, 2);
    decoded_signals['a'] = diff(input3,input2)[0];

    // (6,6,6) -> g,e
    auto input4 = find_lenX(display.inputs, 4);
    auto sixes = find_all_lenX(display.inputs, 6);
    auto GEs = sub_from_all(sixes, union_of(input4, STRC(decoded_signals['a'])));
    decoded_signals['g'] = find_lenX(GEs,1)[0];
    decoded_signals['e'] = diff(find_lenX(GEs,2), STRC(decoded_signals['g']))[0];

    //(5,5,5) -> b,d
    auto fives = find_all_lenX(display.inputs, 5);
    std::string EG = STRC(decoded_signals['g']) + STRC(decoded_signals['e']);
    auto BDs = sub_from_all(fives, union_of(input3, EG));
    decoded_signals['d'] = find_lenX(BDs,1)[0];
    decoded_signals['b'] = diff(find_lenX(BDs,2), STRC(decoded_signals['d']))[0];


    //(6,6,6) -> f,c
    auto input7 = find_lenX(display.inputs, 7);
    std::string ABDEG = diff(input7, input2);
    auto CFs = sub_from_all(sixes, ABDEG);
    decoded_signals['f'] = find_lenX(CFs,1)[0];
    decoded_signals['c'] = diff(find_lenX(CFs,2), STRC(decoded_signals['f']))[0];


    Decoder signal_to_normal;
    for ( auto& [k,v]: decoded_signals)
    {
        signal_to_normal[v] = k;
    }
    return signal_to_normal;
}

int day08lib::decode_output( const std::string& output, const day08lib::Decoder& decoder)
{
    std::string decoded_output;
    for (auto c : output)
    {
        decoded_output += decoder.at(c);
    }
    std::sort(decoded_output.begin(), decoded_output.end());

    for (auto& [v,s] : normal_signals)
    {
        if (decoded_output == s)
        {
            return v;
        }
    }

    return 0;
}


day08lib::DigitalDisplays day08lib::parse_datastream(std::istream& data_stream)
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



size_t day08lib::decode_display( const day08lib::DigitalDisplay& display)
{
    auto decoder = create_decoder(display);
    return std::accumulate(display.outputs.cbegin(), display.outputs.cend(), 0,
                                                [decoder](auto t, const auto& d)
                                                {
                                                    return t*10 + decode_output(d, decoder);
                                                }
                        );

}

std::size_t day08lib::part2_solve(std::istream& data_stream)
{
    auto displays = parse_datastream(data_stream);

    return std::accumulate(displays.cbegin(), displays.cend(), 0,
                                                [](auto t, const auto& d)
                                                {
                                                    return t + decode_display(d);
                                                }
                                    );
}
