#include "aoc/day02.h"
#include "aoc/day02_lib.h"
#include <iostream>
#include <fstream>

using namespace day02lib;

int day02(const std::string& filename)
{
    std::ifstream datafile(filename);
    if(!datafile)
    {
        std::cout << "Error opening input file" << std::endl;
        return -1;
    }
    std::cout << "Day 2 Part 1 Solution= " << part1_solve(datafile) << std::endl;

    std::ifstream datafile2(filename);
    std::cout << "Day 2 Part 2 Solution= " << part2_solve(datafile2) << std::endl;

    return -1;
}
