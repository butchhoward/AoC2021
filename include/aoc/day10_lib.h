#ifndef DAY10_LIB_H
#define DAY10_LIB_H
#include <iostream>
#include <cstddef>
#include <tuple>
#include <vector>

namespace day10lib {


std::size_t part1_solve(std::istream& data_stream);
std::size_t part2_solve(std::istream& data_stream);



typedef std::string NavLine;
typedef std::vector<NavLine> NavSystem;
std::ostream & operator<<(std::ostream &os, const NavSystem& things);

typedef std::tuple<bool, char, std::string> ValidateReturnType;
ValidateReturnType validate_nav_line(const NavLine& nav_line);

NavSystem parse_datastream(std::istream& data_stream);

std::size_t calculate_finishing_score(const std::string& finishing);


}
#endif
