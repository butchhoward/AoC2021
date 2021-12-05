#include "aoc/day03_lib.h"

#include <iostream>
#include <sstream>
#include <cstddef>
#include <vector>
#include <map>
#include <set>
#include <tuple>
#include <algorithm>
#include <numeric>
#include <functional>
#include <ranges>


using namespace day03lib;

namespace {

typedef std::vector<bool> DiagnosticCode;
typedef std::vector<DiagnosticCode> DiagnosticCodes;

int diagnostic_code_to_int(DiagnosticCode c)
{
    int value{0};
    for ( auto b : c)
    {
        value = value << 1;
        value |= b ? 1 : 0;
    }
    return value;
}

// std::string diagnostic_code_to_string(DiagnosticCode c)
// {
//     std::string s;
//     for (auto b : c)
//     {
//         s += b ? "1" : "0";
//     }
//     return s;
// }

DiagnosticCodes parse_datastream(std::istream& data_stream)
{
    DiagnosticCodes codes;

    std::string line;
    for (;std::getline(data_stream, line);)
    {
        DiagnosticCode c;
        for ( auto s : line )
        {
            c.push_back(s == '1');
        }
        codes.push_back( c );
    }

    return codes;
}


std::tuple<int, int> count_bits( const DiagnosticCodes& codes, size_t pos)
{
    int ones_count{0}, zeros_count{0};

    for ( auto c : codes)
    {
        if (c[pos])
        {
            ++ones_count;
        }
        else
        {
            ++zeros_count;
        }
    }

    return std::tuple<int,int>(ones_count, zeros_count);
}

DiagnosticCodes filter_codes(const DiagnosticCodes& codes, size_t pos, bool bit_value)
{
    auto f = codes | std::views::filter( [pos, bit_value](auto c)
                                            { return c[pos] == bit_value; }
                                       );
    return DiagnosticCodes(f.begin(), f.end());
}

DiagnosticCode oxygen_rating(const DiagnosticCodes& cs)
{
    DiagnosticCodes codes(cs);
    size_t pos{0};

    while (codes.size() > 1)
    {
        auto [ones, zeros] = count_bits(codes, pos);
        codes = filter_codes(codes, pos, ones >= zeros);
        ++pos;
    }

    return codes[0];
}

DiagnosticCode c02_rating(const DiagnosticCodes& cs)
{
    DiagnosticCodes codes(cs);
    size_t pos{0};

    while (codes.size() > 1)
    {
        auto [ones, zeros] = count_bits(codes, pos);
        codes = filter_codes(codes, pos, ones < zeros);
        ++pos;
    }

    return codes[0];
}

} //namespace

std::size_t day03lib::part1_solve(std::istream& data_stream)
{
    auto codes = parse_datastream(data_stream);

    DiagnosticCode exemplar = codes[0];
    std::vector<int> one_counts(exemplar.size(), 0);
    std::vector<int> zero_counts(exemplar.size(), 0);

    for ( auto c : codes)
    {
        for (size_t i = 0; i < exemplar.size(); ++i)
        {
            if (c[i])
            {
                one_counts[i] = one_counts[i] + 1;
            }
            else
            {
                zero_counts[i] = zero_counts[i] + 1;
            }
        }
    }

    DiagnosticCode gamma;
    DiagnosticCode epsilon;

    for (size_t i = 0; i < exemplar.size(); ++i)
    {
        gamma.push_back(one_counts[i] > zero_counts[i]);
        epsilon.push_back(zero_counts[i] >= one_counts[i]);
    }

    // std::cout << diagnostic_code_to_string(gamma) << "=" << diagnostic_code_to_int(gamma) << " "
    //           << diagnostic_code_to_string(epsilon) << "=" << diagnostic_code_to_int(epsilon) << std::endl;

    return diagnostic_code_to_int(gamma) * diagnostic_code_to_int(epsilon);
}

std::size_t day03lib::part2_solve(std::istream& data_stream)
{
    auto codes = parse_datastream(data_stream);

    auto oxy = oxygen_rating(codes);
    auto c02 = c02_rating(codes);

    return diagnostic_code_to_int(oxy) * diagnostic_code_to_int(c02);
}
