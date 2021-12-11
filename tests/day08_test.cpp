#include "gtest/gtest.h"

#include "day08_test.h"
#include <aoc/day08_lib.h>

#include <sstream>
#include <fstream>
#include <string>

using namespace day08lib;
using namespace day08test;

namespace {

std::string sample_data =
    "be cfbegad cbdgef fgaecd cgeb fdcge agebfd fecdb fabcd edb | fdgacbe cefdb cefbgd gcbe\n"
    "edbfga begcd cbg gc gcadebf fbgde acbgfd abcde gfcbed gfec | fcgedb cgb dgebacf gc\n"
    "fgaebd cg bdaec gdafb agbcfd gdcbef bgcad gfac gcb cdgabef | cg cg fdcagb cbg\n"
    "fbegcd cbd adcefb dageb afcb bc aefdc ecdab fgdeca fcdbega | efabcd cedba gadfec cb\n"
    "aecbfdg fbg gf bafeg dbefa fcge gcbea fcaegb dgceab fcbdga | gecf egdcabf bgf bfgea\n"
    "fgeab ca afcebg bdacfeg cfaedg gcfdb baec bfadeg bafgc acf | gebdcfa ecba ca fadegcb\n"
    "dbcfg fgd bdegcaf fgec aegbdf ecdfab fbedc dacgb gdcebf gf | cefg dcbef fcge gbcadfe\n"
    "bdfegc cbegaf gecbf dfcage bdacg ed bedf ced adcbefg gebcd | ed bcgafe cdgba cbgef\n"
    "egadfb cdbfeg cegd fecab cgb gbdefca cg fgcdab egfdb bfceg | gbdfcae bgc cg cgb\n"
    "gcafb gcf dcaebfg ecagb gf abcdeg gaef cafbge fdbac fegbdc | fgae cfgab fg bagce\n"
    ;

TEST( day08, test_sample_data ) {
    std::istringstream data_stream(sample_data);
    auto p = part1_solve(data_stream);
    EXPECT_EQ(26, p);
}

TEST( day08, test_data_1 ) {
    std::string data_file_name = "../data/day08_data.txt";
    std::ifstream datafile(data_file_name);
    ASSERT_TRUE(datafile) << "Error opening input file" << std::endl;

    auto p1 = part1_solve(datafile);

    EXPECT_EQ(383, p1);
}

// TEST( day08, test_sample_data_part2 ) {
//     std::istringstream data_stream(sample_data);
//     auto p = part2_solve(data_stream);
//     EXPECT_EQ(999999999, p);
// }

// TEST( day08, test_data_2 )
// {
//     std::string data_file_name = "../data/day08_data.txt";
//     std::ifstream datafile(data_file_name);
//     ASSERT_TRUE(datafile) << "Error opening input file" << std::endl;

//     auto p2 = part2_solve(datafile);

//     EXPECT_EQ(999999999, p2);
// }

}
