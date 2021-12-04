#include "gtest/gtest.h"

#include "./day01_test.h"
#include <aoc/day01_lib.h>
#include <sstream>
#include <fstream>
#include <string>

using namespace day01lib;
using namespace day01test;

namespace {

std::string sample_data_1 = 
    "199\n"
    "200\n"
    "208\n"
    "210\n"
    "200\n"
    "207\n"
    "240\n"
    "269\n"
    "260\n"
    "263\n"
    ;

std::string sample_data_2 = 
    "199  A      \n"
    "200  A B    \n"
    "208  A B C  \n"
    "210    B C D\n"
    "200  E   C D\n"
    "207  E F   D\n"
    "240  E F G  \n"
    "269    F G H\n"
    "260      G H\n"
    "263        H\n"
    ;


TEST( day01, test_sample_data ) 
{
    std::istringstream data_stream(sample_data_1);
    auto p = part1_solve(data_stream);
    EXPECT_EQ(7, p);
}

TEST( day01, test_sample_data_part2 ) 
{
    std::istringstream data_stream(sample_data_2);
    auto p = part2_solve(data_stream);
    EXPECT_EQ(5, p);
}

TEST( day01, test_data_1 ) 
{
    std::string data_file_name = "../data/day01_data.txt";
    std::ifstream datafile(data_file_name);
    ASSERT_TRUE(datafile) << "Error opening input file" << std::endl;

    auto p1 = part1_solve(datafile);

    EXPECT_EQ(1292, p1);
}

TEST( day01, test_data_2 ) 
{
    std::string data_file_name = "../data/day01_data.txt";
    std::ifstream datafile(data_file_name);
    ASSERT_TRUE(datafile) << "Error opening input file" << std::endl;

    auto p2 = part2_solve(datafile);

    EXPECT_EQ(999999999, p2);
}

}
