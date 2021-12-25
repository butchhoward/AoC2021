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

std::vector<int> sample_data_decoded_output= {
    8394
    ,9781
    ,1197
    ,9361
    ,4873
    ,8418
    ,4548
    ,1625
    ,8717
    ,4315
};

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

TEST( day08, test_create_decoder ) 
{
    // std::istringstream data_stream("be cfbegad cbdgef fgaecd cgeb fdcge agebfd fecdb fabcd edb | fdgacbe cefdb cefbgd gcbe\n");
    std::istringstream data_stream("abcefg cf acdeg acdfg bdcf abdfg abdefg acf abcdefg abcdfg| acdfg abdfg abcdefg acf\n");

    auto displays = parse_datastream(data_stream);

    auto decoder = create_decoder(displays[0]);
    
    Decoder expected_decoder;
    expected_decoder['a'] = 'a';
    expected_decoder['b'] = 'b';
    expected_decoder['c'] = 'c';
    expected_decoder['d'] = 'd';
    expected_decoder['e'] = 'e';
    expected_decoder['f'] = 'f';
    expected_decoder['g'] = 'g';

    for (auto& [k,v]: decoder)
    {
        EXPECT_EQ( v, expected_decoder[k]);
    }
}


TEST( day08, test_sample_data_decoded ) 
{
    std::istringstream data_stream(sample_data);
    auto displays = parse_datastream(data_stream);

    auto display = displays.cbegin();
    auto expeced_decoded_outout = sample_data_decoded_output.cbegin();
    for (; display != displays.cend(); ++display, ++expeced_decoded_outout )
    {
        EXPECT_EQ( decode_display(*display), *expeced_decoded_outout);
    }

    // auto decoder = create_decoder(displays[7]);
    // std::cout << "====" << std::endl << displays[7] << std::endl << decoder << std::endl;

    // EXPECT_EQ( decode_display(displays[7]), sample_data_decoded_output[7]);

}

TEST( day08, test_sample_data_part2 ) {
    std::istringstream data_stream(sample_data);
    auto p = part2_solve(data_stream);
    EXPECT_EQ(61229, p);
}

TEST( day08, test_data_2 )
{
    std::string data_file_name = "../data/day08_data.txt";
    std::ifstream datafile(data_file_name);
    ASSERT_TRUE(datafile) << "Error opening input file" << std::endl;

    auto p2 = part2_solve(datafile);

    EXPECT_EQ(998900, p2);
}

}
