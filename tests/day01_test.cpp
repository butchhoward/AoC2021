#include "./day01_test.h"
#include <aoc/day01_lib.h>
#include "test_runner.h"
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


bool test_sample_data()
{
    std::istringstream data_stream(sample_data);
    auto p = part1_solve(data_stream);
    return 999999999 == p;
}

bool test_sample_data_part2()
{
    std::istringstream data_stream(sample_data);
    auto p = part2_solve(data_stream);
    return 999999999 == p;
}

bool test_data()
{
    std::string data_file_name = "./data/day01_data.txt";

    std::ifstream datafile(data_file_name);
    if(!datafile)
    {
        std::cout << "Error opening input file" << std::endl;
        return false;
    }
    auto p1 = part1_solve(datafile);

    std::ifstream datafile2(data_file_name);
    auto p2 = part2_solve(datafile2);

    return     (999999999 == p1)
            && (999999999 == p2)
           ;
}


}

bool day01test::day01_test()
{
   test_runner::Tests tests = {
        {"test_sample_data", test_sample_data}
        ,{"test_sample_data_part2", test_sample_data_part2}
        ,{"test_data", test_data}
    };

    return test_runner::run_tests("day01_test", tests);
}
