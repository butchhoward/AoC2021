#ifndef DAY09_LIB_H
#define DAY09_LIB_H

#include <library/points.h>

#include <iostream>
#include <cstddef>
#include <vector>

namespace day09lib {

std::size_t part1_solve(std::istream& data_stream);
std::size_t part2_solve(std::istream& data_stream);

typedef int Height;

typedef std::vector<Height> HeightRow;
std::ostream & operator<<(std::ostream &os, const HeightRow& row);

typedef std::vector<HeightRow> HeightMap;
std::ostream & operator<<(std::ostream &os, const HeightMap& map);

typedef Points Basin;

typedef std::vector<Basin> Basins;
std::ostream & operator<<(std::ostream &os, const Basins& basins);



HeightMap parse_datastream(std::istream& data_stream);


}
#endif
