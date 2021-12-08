#include "gtest/gtest.h"

#include "day06_test.h"
#include <aoc/day06_lib.h>

#include <sstream>
#include <fstream>
#include <string>

using namespace day06lib;
using namespace day06test;

namespace {

std::string sample_data =
    "3,4,3,1,2\n"
    ;

TEST( day06, test_sample_data_part1_80 ) {
    std::istringstream data_stream(sample_data);
    auto p = part1_solve(data_stream, 80);
    EXPECT_EQ(5934, p);
}

TEST( day06, test_sample_data_part1_18 ) {
    std::istringstream data_stream(sample_data);
    auto p = part1_solve(data_stream, 18);
    EXPECT_EQ(26, p);
}

// TEST( day06, test_sample_data_part2 ) {
//     std::istringstream data_stream(sample_data);
//     auto p = part2_solve(data_stream);
//     EXPECT_EQ(999999999, p);
// }

// TEST( day06, test_data_1 ) {
//     std::string data_file_name = "../data/day06_data.txt";
//     std::ifstream datafile(data_file_name);
//     ASSERT_TRUE(datafile) << "Error opening input file" << std::endl;

//     auto p1 = part1_solve(datafile);

//     EXPECT_EQ(999999999, p1);
// }

// TEST( day06, test_data_2 )
// {
//     std::string data_file_name = "../data/day06_data.txt";
//     std::ifstream datafile(data_file_name);
//     ASSERT_TRUE(datafile) << "Error opening input file" << std::endl;

//     auto p2 = part2_solve(datafile);

//     EXPECT_EQ(999999999, p2);
// }

}
