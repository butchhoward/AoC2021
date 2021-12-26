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

TEST( day10, test_validate_mystery ) 
{
    NavLine n = "[({(<(())[]>[[{[]{<()<>>";
    auto [v,c,f] = validate_nav_line(n);

    EXPECT_TRUE(v);
    EXPECT_EQ(c, '\0');
}

TEST( day10, test_validate ) 
{
    typedef struct Data {
        NavLine n;
        char c;
        bool v;
        std::string f;
    } Data;

    std::vector<Data> test_data
    {
        {"{([(<{}[<>[]}>{[]{[(<()>", '}', false, ""},
        {"[[<[([]))<([[{}[[()]]]", ')', false, ""},
        {"[{[{({}]{}}([{[{{{}}([]", ']', false, ""},
        {"[<(<(<(<{}))><([]([]()", ')', false, ""},
        {"<{([([[(<>()){}]>(<<{{", '>', false, ""},
    
        {"[({(<(())[]>[[{[]{<()<>>", '\0', true, "}}]])})]"},
        {"[(()[<>])]({[<{<<[]>>(",'\0', true, ")}>]})"},
        {"(((({<>}<{<{<>}{[]{[]{}",'\0', true, "}}>}>))))"},
        {"{<[[]]>}<{[{[{[]{()[[[]",'\0', true, "]]}}]}]}>"},
        {"<{([{{}}[<[[[<>{}]]]>[]]",'\0', true, "])}>"}
    };

    for ( auto d : test_data)
    {
        auto [v,c,f] = validate_nav_line(d.n);

        EXPECT_EQ(v, d.v) << d.n;
        EXPECT_EQ(c, d.c);
        EXPECT_EQ(f, d.f) << d.f;
    }
}

TEST( day10, test_data_1 ) {
    std::string data_file_name = "../data/day10_data.txt";
    std::ifstream datafile(data_file_name);
    ASSERT_TRUE(datafile) << "Error opening input file" << std::endl;

    auto p1 = part1_solve(datafile);

    EXPECT_EQ(411471, p1);
}

TEST( day10, test_sample_data_part2 ) {
    std::istringstream data_stream(sample_data);
    auto p = part2_solve(data_stream);
    EXPECT_EQ(288957, p);
}

TEST( day10, test_calculate_finishing_score ) 
{
    typedef struct Data {
        std::string f;
        unsigned long long s;
    } Data;

    std::vector<Data> test_data
    {
        {"}}]])})]", 288957},
        {")}>]})", 5566},
        {"}}>}>))))", 1480781},
        {"]]}}]}]}>", 995444},
        {"])}>", 294}
    };

    for (auto d : test_data)
    {
        auto score = calculate_finishing_score(d.f);
        EXPECT_EQ(score, d.s);
    }
}

TEST( day10, test_data_2 )
{
    std::string data_file_name = "../data/day10_data.txt";
    std::ifstream datafile(data_file_name);
    ASSERT_TRUE(datafile) << "Error opening input file" << std::endl;

    auto p2 = part2_solve(datafile);

    EXPECT_EQ(3122628974, p2);
}

}
