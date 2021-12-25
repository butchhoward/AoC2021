#include "aoc/day09_lib.h"
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


#pragma GCC diagnostic ignored "-Wunused-function"
std::ostream & day09lib::operator<<(std::ostream &os, const Basins& basins)
{
    for (auto b : basins)
    {
        os << "->" << b << std::endl;
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

    auto get_adjacent = [map](size_t row, size_t col, int v, int h)
                        {
                            auto columns = map[0].size();
                            auto rows = map.size();

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

bool is_alreay_in_basin(const Basins& basins, const Point& p)
{
    return std::any_of(basins.cbegin(), basins.cend(),
                    [p](const auto& b)
                    {
                        return b.cend() != std::find(b.cbegin(), b.cend(), p);
                    }
        );
};

void check_basin(const Point& p, const HeightMap& map, Basin& new_basin)
{

    auto already_added = [&new_basin](const Point& p)
    {
        return std::find(new_basin.cbegin(), new_basin.cend(), p) != new_basin.cend();
    };

    auto add_point = [&map, &new_basin, already_added](const Point& new_point)
    {
        if (map[new_point.y][new_point.x] != 9)
        {
            if (already_added(new_point))
                return false;

            new_basin.push_back(new_point);
            check_basin(new_point, map, new_basin);
            return true;
        }

        return false;
    };

    auto crawl_map = [&map, add_point](const Point& p, int x_adj, int y_adj)
    {

        for (auto [x,y] = std::tuple{p.x + x_adj, p.y + y_adj}; 
            x < (int)map[0].size() && x >= 0 && y < (int)map.size() && y >= 0; 
            x+=x_adj, y+=y_adj
        )
        {
            Point new_point(x, y);
            if (!add_point(new_point))
            {
                break;
            }
        }

    };

    crawl_map(p, 1, 0);
    crawl_map(p, -1, 0);
    crawl_map(p, 0, 1);
    crawl_map(p, 0, -1);
}

Basins find_basins(const HeightMap& map)
{
    Basins basins;

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
            if (*height == 9)
                continue;    

            Point p(current_col, current_row);

            if (is_alreay_in_basin(basins, p))
            {
                continue;
            }

            Basin new_basin;
            new_basin.push_back(p);
            check_basin(p, map, new_basin);
            basins.push_back(new_basin);
        }
    }

    return basins;
}


} //end of namespace



std::size_t day09lib::part1_solve(std::istream& data_stream)
{
    auto map = parse_datastream(data_stream);
    auto lowpoints = find_lowpoints(map);
    return total_risk(lowpoints);
}

std::size_t day09lib::part2_solve(std::istream& data_stream)
{
    auto map = parse_datastream(data_stream);
    auto basins = find_basins(map);

    //sort basin sizes
    std::vector<size_t> sizes;
    for ( auto b : basins)
    {
        sizes.push_back(b.size());
    }
    std::sort(sizes.begin(), sizes.end());

    //take largest 3
    while (sizes.size() > 3)
        sizes.erase(sizes.cbegin());

    //return product of sizes
    return std::accumulate(sizes.cbegin(), sizes.cend(), 1,
                [](auto t, auto s){ return t * s;}
            );

}
