#include "gtest/gtest.h"

#include "./day01_test.h"
#include <aoc/day01_lib.h>
#include <sstream>
#include <fstream>
#include <string>

using namespace day01lib;
using namespace day01test;

namespace {

std::string sample_data = 
    "xx\n"
    "xx\n"
    ;


TEST( day01, test_sample_data ) {
    std::istringstream data_stream(sample_data);
    auto p = part1_solve(data_stream);
    EXPECT_EQ(999999999, p);
}

TEST( day01, test_sample_data_part2 ) {
    std::istringstream data_stream(sample_data);
    auto p = part2_solve(data_stream);
    EXPECT_EQ(999999999, p);
}

TEST( day01, test_data ) {
    std::string data_file_name = "./data/day01_data.txt";

    std::ifstream datafile(data_file_name);
    ASSERT_TRUE(datafile) << "Error opening input file" << std::endl;

    auto p1 = part1_solve(datafile);

    std::ifstream datafile2(data_file_name);
    auto p2 = part2_solve(datafile2);

    EXPECT_EQ(999999999, p1);
    EXPECT_EQ(999999999, p2);
}


}
