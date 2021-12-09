#include "gtest/gtest.h"

#include "day07_test.h"
#include <aoc/day07_lib.h>

#include <sstream>
#include <fstream>
#include <string>

using namespace day07lib;
using namespace day07test;

namespace {

std::string sample_data =
    "16,1,2,0,4,2,7,1,2,14\n"
    ;

TEST( day07, test_sample_data ) {
    std::istringstream data_stream(sample_data);
    auto p = part1_solve(data_stream);
    EXPECT_EQ(37, p);
}

TEST( day07, test_data_1 ) {
    std::string data_file_name = "../data/day07_data.txt";
    std::ifstream datafile(data_file_name);
    ASSERT_TRUE(datafile) << "Error opening input file" << std::endl;

    auto p1 = part1_solve(datafile);

    EXPECT_EQ(356958, p1);
}

TEST( day07, test_sample_data_part2 ) {
    std::istringstream data_stream(sample_data);
    auto p = part2_solve(data_stream);
    EXPECT_EQ(168, p);
}


TEST( day07, test_data_2 )
{
    std::string data_file_name = "../data/day07_data.txt";
    std::ifstream datafile(data_file_name);
    ASSERT_TRUE(datafile) << "Error opening input file" << std::endl;

    auto p2 = part2_solve(datafile);

    EXPECT_EQ(105461913, p2);
}

}
