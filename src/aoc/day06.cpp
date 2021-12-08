#include "aoc/day06.h"
#include "aoc/day06_lib.h"
#include <iostream>
#include <fstream>

using namespace day06lib;

int day06(const std::string& filename)
{
    std::ifstream datafile(filename);
    if(!datafile)
    {
        std::cout << "Error opening input file" << std::endl;
        return -1;
    }
    std::cout << "Day 6 Part 1 Solution= " << part1_solve(datafile, 80) << std::endl;

    std::ifstream datafile2(filename);
    std::cout << "Day 6 Part 2 Solution= " << part2_solve(datafile2, 256) << std::endl;

    return -1;
}
