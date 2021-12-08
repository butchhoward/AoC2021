#include "gtest/gtest.h"

#include "day05_test.h"
#include <aoc/day05_lib.h>

#include <sstream>
#include <fstream>
#include <string>

using namespace day05lib;
using namespace day05test;

namespace {

std::string sample_data =
    "0,9 -> 5,9\n"
    "8,0 -> 0,8\n"
    "9,4 -> 3,4\n"
    "2,2 -> 2,1\n"
    "7,0 -> 7,4\n"
    "6,4 -> 2,0\n"
    "0,9 -> 2,9\n"
    "3,4 -> 1,4\n"
    "0,0 -> 8,8\n"
    "5,5 -> 8,2\n"
;

TEST( day05, test_sample_data ) {
    std::istringstream data_stream(sample_data);
    auto p = part1_solve(data_stream);
    EXPECT_EQ(5, p);
}

// TEST( day05, test_sample_data_part2 ) {
//     std::istringstream data_stream(sample_data);
//     auto p = part2_solve(data_stream);
//     EXPECT_EQ(999999999, p);
// }

TEST( day05, test_data_1 ) {
    std::string data_file_name = "../data/day05_data.txt";
    std::ifstream datafile(data_file_name);
    ASSERT_TRUE(datafile) << "Error opening input file" << std::endl;

    auto p1 = part1_solve(datafile);

    EXPECT_EQ(8622, p1);
}

// TEST( day05, test_data_2 )
// {
//     std::string data_file_name = "../data/day05_data.txt";
//     std::ifstream datafile(data_file_name);
//     ASSERT_TRUE(datafile) << "Error opening input file" << std::endl;

//     auto p2 = part2_solve(datafile);

//     EXPECT_EQ(999999999, p2);
// }

}
