#include "gtest/gtest.h"

#include "day03_test.h"
#include <aoc/day03_lib.h>

#include <sstream>
#include <fstream>
#include <string>

using namespace day03lib;
using namespace day03test;

namespace {

std::string sample_data =
    "00100\n"
    "11110\n"
    "10110\n"
    "10111\n"
    "10101\n"
    "01111\n"
    "00111\n"
    "11100\n"
    "10000\n"
    "11001\n"
    "00010\n"
    "01010\n"
    ;

TEST( day03, test_sample_data ) {
    std::istringstream data_stream(sample_data);
    auto p = part1_solve(data_stream);
    EXPECT_EQ(198, p);
}

// TEST( day03, test_sample_data_part2 ) {
//     std::istringstream data_stream(sample_data);
//     auto p = part2_solve(data_stream);
//     EXPECT_EQ(999999999, p);
// }

TEST( day03, test_data_1 ) {
    std::string data_file_name = "../data/day03_data.txt";
    std::ifstream datafile(data_file_name);
    ASSERT_TRUE(datafile) << "Error opening input file" << std::endl;

    auto p1 = part1_solve(datafile);

    EXPECT_EQ(3959450, p1);
}

// TEST( day03, test_data_2 )
// {
//     std::string data_file_name = "../data/day03_data.txt";
//     std::ifstream datafile(data_file_name);
//     ASSERT_TRUE(datafile) << "Error opening input file" << std::endl;

//     auto p2 = part2_solve(datafile);

//     EXPECT_EQ(999999999, p2);
// }

}
