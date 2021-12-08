#include "gtest/gtest.h"

#include "day04_test.h"
#include <aoc/day04_lib.h>

#include <sstream>
#include <fstream>
#include <string>

using namespace day04lib;
using namespace day04test;

namespace {

std::string sample_data =
     "7,4,9,5,11,17,23,2,0,14,21,24,10,16,13,6,15,25,12,22,18,20,8,19,3,26,1\n"
    "\n"
    "22 13 17 11  0\n"
    " 8  2 23  4 24\n"
    "21  9 14 16  7\n"
    " 6 10  3 18  5\n"
    " 1 12 20 15 19\n"
    "\n"
    " 3 15  0  2 22\n"
    " 9 18 13 17  5\n"
    "19  8  7 25 23\n"
    "20 11 10 24  4\n"
    "14 21 16 12  6\n"
    "\n"
    "14 21 17 24  4\n"
    "10 16 15  9 19\n"
    "18  8 23 26 20\n"
    "22 11 13  6  5\n"
    " 2  0 12  3  7\n"
    "\n"
;

TEST( day04, test_sample_data ) {
    std::istringstream data_stream(sample_data);
    auto p = part1_solve(data_stream);
    EXPECT_EQ(4512, p);
}

TEST( day04, test_sample_data_part2 ) {
    std::istringstream data_stream(sample_data);
    auto p = part2_solve(data_stream);
    EXPECT_EQ(1924, p);
}

TEST( day04, test_data_1 ) {
    std::string data_file_name = "../data/day04_data.txt";
    std::ifstream datafile(data_file_name);
    ASSERT_TRUE(datafile) << "Error opening input file" << std::endl;

    auto p1 = part1_solve(datafile);

    EXPECT_EQ(10680, p1);
}

TEST( day04, test_data_2 )
{
    std::string data_file_name = "../data/day04_data.txt";
    std::ifstream datafile(data_file_name);
    ASSERT_TRUE(datafile) << "Error opening input file" << std::endl;

    auto p2 = part2_solve(datafile);

    EXPECT_EQ(31892, p2);
}

}
