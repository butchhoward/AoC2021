#include "aoc/day09_lib.h"

#include <iostream>
#include <sstream>
#include <cstddef>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <functional>

using namespace day09lib;


std::ostream & day09lib::operator<<(std::ostream &os, const HeightRow& row)
{
    for (auto height : row)
    {
        os << height;
    }
    return os;
}

#pragma GCC diagnostic ignored "-Wunused-function"
std::ostream & day09lib::operator<<(std::ostream &os, const HeightMap& map)
{
    for (auto row : map)
    {
        os << row << std::endl;
    }
    return os;
}

HeightMap day09lib::parse_datastream(std::istream& data_stream)
{
    HeightMap heightmap;

    std::string line;
    for (;std::getline(data_stream, line);)
    {
        std::istringstream v(line);

        HeightRow row;
        for (auto h : line)
        {
            int height{0};
            std::istringstream s_value(std::string(1,h));
            s_value >> height;

            row.push_back(height);
        }
        heightmap.push_back(row);
    }

    return heightmap;
}


namespace {

HeightRow find_lowpoints(const HeightMap& map)
{
    HeightRow lowpoints;
    auto columns = map[0].size();
    auto rows = map.size();

    auto get_adjacent = [map, columns, rows](size_t row, size_t col, int v, int h)
                        {
                            if ( (row == 0 && v < 0) ||
                                 (row >= rows-1 && v > 0) ||
                                 (col == 0 && h < 0) ||
                                 (col >= columns-1 && h > 0)
                            )
                            {
                                return 9;
                            }

                            return map[row+v][col+h];
                        };

    for (auto [current_row, row] = std::tuple{size_t(0), map.cbegin()}; 
            row != map.cend(); 
            ++current_row, ++row
    )
    {
        for (auto [current_col, height] = std::tuple{size_t(0), row->cbegin()}; 
             height != row->cend();
             ++current_col, ++height
        )
        {
                HeightRow adjacents;
                adjacents.push_back( get_adjacent(current_row, current_col, -1, 0));
                adjacents.push_back( get_adjacent(current_row, current_col, 0, -1));
                adjacents.push_back( get_adjacent(current_row, current_col, 1, 0));
                adjacents.push_back( get_adjacent(current_row, current_col, 0, 1));

                if (std::all_of(adjacents.cbegin(), adjacents.cend(), 
                                    [height](auto a) { return a > *height; }
                                )
                )
                {
                    lowpoints.push_back(*height);
                }

        }
    }

    return lowpoints;
}

size_t total_risk(const HeightRow& lowpoints)
{
    return std::accumulate(lowpoints.cbegin(), lowpoints.cend(), 0,
                            [](auto t, auto h)
                            {
                                return t + (1+h);
                            }
                        );

}



}

std::size_t day09lib::part1_solve(std::istream& data_stream)
{
    auto map = parse_datastream(data_stream);
    auto lowpoints = find_lowpoints(map);
    return total_risk(lowpoints);
}

std::size_t day09lib::part2_solve(std::istream& data_stream)
{
    auto things = parse_datastream(data_stream);
    return 0;
}
