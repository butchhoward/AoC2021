#include "gtest/gtest.h"

#include "day10_test.h"
#include <aoc/day10_lib.h>

#include <sstream>
#include <fstream>
#include <string>

using namespace day10lib;
using namespace day10test;

namespace {

std::string sample_data =
    "[({(<(())[]>[[{[]{<()<>>\n"
    "[(()[<>])]({[<{<<[]>>(\n"
    "{([(<{}[<>[]}>{[]{[(<()>\n"
    "(((({<>}<{<{<>}{[]{[]{}\n"
    "[[<[([]))<([[{}[[()]]]\n"
    "[{[{({}]{}}([{[{{{}}([]\n"
    "{<[[]]>}<{[{[{[]{()[[[]\n"
    "[<(<(<(<{}))><([]([]()\n"
    "<{([([[(<>()){}]>(<<{{\n"
    "<{([{{}}[<[[[<>{}]]]>[]]\n"
    ;

TEST( day10, test_sample_data ) {
    std::istringstream data_stream(sample_data);
    auto p = part1_solve(data_stream);
    EXPECT_EQ(26397, p);
}

TEST( day10, test_validate ) 
{
    NavLine n = "{([(<{}[<>[]}>{[]{[(<()>"; // - Expected ], but found } instead

    auto [v,c] = validate_nav_line(n);

    EXPECT_FALSE(v);
    EXPECT_EQ(c, '}');
}

// TEST( day10, test_data_1 ) {
//     std::string data_file_name = "../data/day10_data.txt";
//     std::ifstream datafile(data_file_name);
//     ASSERT_TRUE(datafile) << "Error opening input file" << std::endl;

//     auto p1 = part1_solve(datafile);

//     EXPECT_EQ(999999999, p1);
// }

// TEST( day10, test_sample_data_part2 ) {
//     std::istringstream data_stream(sample_data);
//     auto p = part2_solve(data_stream);
//     EXPECT_EQ(999999999, p);
// }

// TEST( day10, test_data_2 )
// {
//     std::string data_file_name = "../data/day10_data.txt";
//     std::ifstream datafile(data_file_name);
//     ASSERT_TRUE(datafile) << "Error opening input file" << std::endl;

//     auto p2 = part2_solve(datafile);

//     EXPECT_EQ(999999999, p2);
// }

}
