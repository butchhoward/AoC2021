#include "gtest/gtest.h"

#include "day09_test.h"
#include <aoc/day09_lib.h>

#include <sstream>
#include <fstream>
#include <string>

using namespace day09lib;
using namespace day09test;

namespace {

std::string sample_data =
    "2199943210\n"
    "3987894921\n"
    "9856789892\n"
    "8767896789\n"
    "9899965678\n"
    ;

TEST( day09, test_sample_data ) {
    std::istringstream data_stream(sample_data);
    auto p = part1_solve(data_stream);
    EXPECT_EQ(999999999, p);
}

TEST( day09, test_data_1 ) {
    std::string data_file_name = "../data/day09_data.txt";
    std::ifstream datafile(data_file_name);
    ASSERT_TRUE(datafile) << "Error opening input file" << std::endl;

    auto p1 = part1_solve(datafile);

    EXPECT_EQ(999999999, p1);
}

TEST( day09, test_sample_data_part2 ) {
    std::istringstream data_stream(sample_data);
    auto p = part2_solve(data_stream);
    EXPECT_EQ(999999999, p);
}

TEST( day09, test_data_2 )
{
    std::string data_file_name = "../data/day09_data.txt";
    std::ifstream datafile(data_file_name);
    ASSERT_TRUE(datafile) << "Error opening input file" << std::endl;

    auto p2 = part2_solve(datafile);

    EXPECT_EQ(999999999, p2);
}

}
