#include "aoc/day05_lib.h"

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

typedef struct Point {
    int x;
    int y;
} Point;

inline bool operator==(const Point& lhs, const Point& rhs)
{
    return lhs.x == rhs.x &&
           lhs.y == rhs.y;
}
inline bool operator<(const Point& lhs, const Point& rhs)
{
    return lhs.x < rhs.x ||
            (lhs.x == rhs.x && lhs.y < rhs.y);
}

typedef struct Line {
    Point p1;
    Point p2;
} Line;

typedef std::vector<Line> Lines;

typedef std::map<Point, int> Grid;

std::ostream & operator<<(std::ostream &os, const Point& point)
{
    os << "("
       << point.x
       << ","
       << point.y
       << ")"
       ;
    return os;
}
std::ostream & operator<<(std::ostream &os, const Line& line)
{
    os << line.p1
       << " -> "
       << line.p2
       ;

    return os;
}

#pragma GCC diagnostic ignored "-Wunused-function"
std::ostream & operator<<(std::ostream &os, const Lines& lines)
{
    for (auto line : lines)
    {
        os << line << std::endl;
    }
    return os;
}

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
    for (auto line : lines)
    {
        int x1 = std::min(line.p1.x, line.p2.x);
        int x2 = std::max(line.p1.x, line.p2.x);
        int y1 = std::min(line.p1.y, line.p2.y);
        int y2 = std::max(line.p1.y, line.p2.y);

        for (auto x=x1; x <= x2; ++x)
        {
            for (auto y=y1; y <= y2; ++y )
            {
                Point p(x,y);
                int counter{0};
                if (grid.contains(p))
                {
                    counter = grid[p];
                }
                ++counter;

                grid.insert_or_assign(p, counter);
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
    auto things = parse_datastream(data_stream);
    return 0;
}
