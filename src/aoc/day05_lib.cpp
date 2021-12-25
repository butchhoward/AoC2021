#include "aoc/day05_lib.h"
#include "library/points.h"

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

using namespace day05lib;

namespace {



typedef std::map<Point, int> Grid;


typedef std::map<Point, int> Grid;

#pragma GCC diagnostic ignored "-Wunused-function"
std::ostream & operator<<(std::ostream &os, const Grid& grid)
{
    for (const auto& [p, c]: grid)
    {
        os << p
           << ":" << c
           << std::endl
           ;
    }

    return os;
}


Lines parse_datastream(std::istream& data_stream)
{
    Lines data;

    std::string input_line;
    for (;std::getline(data_stream, input_line);)
    {
        std::istringstream v(input_line);

        Line line;
        char comma;
        std::string arrow;
        v >> line.p1.x
          >> comma
          >> line.p1.y;
        v.ignore(4)         //why is there not an iomanip object that does this?
          >> line.p2.x
          >> comma
          >> line.p2.y
          ;

        data.push_back(line);
    }

    return data;
}

std::tuple<Lines, Lines> filter_hv_lines(const Lines& lines)
{
    auto h_lines = lines | std::views::filter( [](auto line)
                                            { return line.p1.x == line.p2.x;
                                            }
                                       );
    auto v_lines = lines | std::views::filter( [](auto line)
                                            { return line.p1.y == line.p2.y;
                                            }
                                       );

    return std::tuple(Lines(h_lines.begin(), h_lines.end()), Lines(v_lines.begin(), v_lines.end()));
}

Grid filter_grid_points(const Grid& grid, int at_least)
{
    auto filtered_grid = grid | std::views::filter( [at_least](auto item)
                                            { return item.second >= at_least;
                                            }
                                       );

    return Grid(filtered_grid.begin(), filtered_grid.end());
}

void update_grid(Grid& grid, const Lines& lines)
{
    auto update_point = [&grid](Point p)
    {
        grid.try_emplace(p, 0);
        int counter = grid[p] + 1;
        grid.insert_or_assign(p, counter);
    };

    for (auto line : lines)
    {
        if ( abs(line.p1.x-line.p2.x) == abs(line.p1.y-line.p2.y))
        {
            int x_inc = line.p1.x <= line.p2.x ? 1 : -1;
            int y_inc = line.p1.y <= line.p2.y ? 1 : -1;

            // 45 degree line
            for (auto x=line.p1.x, y=line.p1.y, steps=0;
                    steps <= abs(line.p1.x-line.p2.x);
                    x+=x_inc, y+=y_inc, ++steps
                )
            {
                update_point(Point(x,y));
            }
        }
        else
        {
            int x1 = std::min(line.p1.x, line.p2.x);
            int x2 = std::max(line.p1.x, line.p2.x);
            int y1 = std::min(line.p1.y, line.p2.y);
            int y2 = std::max(line.p1.y, line.p2.y);

            for (auto x=x1; x <= x2; ++x)
            {
                for (auto y=y1; y <= y2; ++y )
                {
                    update_point(Point(x,y));
                }
            }
        }
    }
}

}

std::size_t day05lib::part1_solve(std::istream& data_stream)
{
    auto lines = parse_datastream(data_stream);

    auto [h_lines, v_lines] = filter_hv_lines(lines);

    Grid grid;
    update_grid(grid, h_lines);
    update_grid(grid, v_lines);

    auto filtered_grid = filter_grid_points(grid, 2);

    return filtered_grid.size();
}

std::size_t day05lib::part2_solve(std::istream& data_stream)
{
    auto lines = parse_datastream(data_stream);

    Grid grid;
    update_grid(grid, lines);

    auto filtered_grid = filter_grid_points(grid, 2);

    return filtered_grid.size();
}
