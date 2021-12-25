#ifndef DAY09_LIB_H
#define DAY09_LIB_H
#include <iostream>
#include <cstddef>
#include <vector>

namespace day09lib {

std::size_t part1_solve(std::istream& data_stream);
std::size_t part2_solve(std::istream& data_stream);

typedef int Height;
typedef std::vector<Height> HeightRow;
typedef std::vector<HeightRow> HeightMap;

HeightMap parse_datastream(std::istream& data_stream);

std::ostream & operator<<(std::ostream &os, const HeightRow& row);
std::ostream & operator<<(std::ostream &os, const HeightMap& map);

}
#endif
