#include "gtest/gtest.h"

#include "day02_test.h"
#include <aoc/day02_lib.h>

#include <sstream>
#include <fstream>
#include <string>

using namespace day02lib;
using namespace day02test;

namespace {

std::string sample_data =
    "forward 5\n"
    "down 5\n"
    "forward 8\n"
    "up 3\n"
    "down 8\n"
    "forward 2\n"
    ;


TEST( day02, test_sample_data ) {
    std::istringstream data_stream(sample_data);
    auto p = part1_solve(data_stream);
    EXPECT_EQ(150, p);
}

TEST( day02, test_sample_data_part2 ) {
    std::istringstream data_stream(sample_data);
    auto p = part2_solve(data_stream);
    EXPECT_EQ(900, p);
}

TEST( day02, test_data_1 ) {
    std::string data_file_name = "../data/day02_data.txt";
    std::ifstream datafile(data_file_name);
    ASSERT_TRUE(datafile) << "Error opening input file" << std::endl;

    auto p1 = part1_solve(datafile);

    EXPECT_EQ(1250395, p1);
}

TEST( day02, test_data_2 )
{
    std::string data_file_name = "../data/day02_data.txt";
    std::ifstream datafile(data_file_name);
    ASSERT_TRUE(datafile) << "Error opening input file" << std::endl;

    auto p2 = part2_solve(datafile);

    EXPECT_EQ(1451210346, p2);
}

}
