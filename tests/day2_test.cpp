#include "gtest/gtest.h"

#include "day2_test.h"
#include <aoc/day2_lib.h>

#include <sstream>
#include <fstream>
#include <string>

using namespace day2lib;
using namespace day2test;

namespace {

std::string sample_data_1 = 
    "xx\n"
    "xx\n"
    ;

std::string sample_data_2 = 
    "xx\n"
    "xx\n"
    ;

TEST( day2, test_sample_data ) {
    std::istringstream data_stream(sample_data_1);
    auto p = part1_solve(data_stream);
    EXPECT_EQ(999999999, p);
}

TEST( day2, test_sample_data_part2 ) {
    std::istringstream data_stream(sample_data_2);
    auto p = part2_solve(data_stream);
    EXPECT_EQ(999999999, p);
}

TEST( day2, test_data_1 ) {
    std::string data_file_name = "../data/day2_data.txt";
    std::ifstream datafile(data_file_name);
    ASSERT_TRUE(datafile) << "Error opening input file" << std::endl;

    auto p1 = part1_solve(datafile);

    EXPECT_EQ(999999999, p1);
}

TEST( day2, test_data_2 )
{
    std::string data_file_name = "../data/day2_data.txt";
    std::ifstream datafile(data_file_name);
    ASSERT_TRUE(datafile) << "Error opening input file" << std::endl;

    auto p2 = part2_solve(datafile);

    EXPECT_EQ(999999999, p2);
}

}
