#!/usr/bin/env bash

# assume running from cpp folder
# ./scripts/make_module DD [module_base_name]
# DD == day number. If not present 999 is used.
# module_name = optional. defaults to 'day'
# 
# Example:
#   ./scripts/make_module 01
# creates library, src_test, src files for day01 with skeleton files

DAY_NUMBER="${1:-999}"
MODULE="${2:-"day"}${DAY_NUMBER}"

MODULEUP=${MODULE^^}

read -r -d '' LIB_HEADER <<-EOT
#ifndef ${MODULEUP}_LIB_H
#define ${MODULEUP}_LIB_H
#include <iostream>
#include <cstddef>

namespace ${MODULE}lib {

std::size_t part1_solve(std::istream& data_stream);
std::size_t part2_solve(std::istream& data_stream);

}
#endif
EOT

read -r -d '' LIB_CPP <<-EOT
#include "${MODULE}_lib.h"

#include <iostream>
#include <sstream>
#include <cstddef>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <functional>

using namespace ${MODULE}lib;

namespace {

typedef int Thing;
typedef std::vector<Thing> Things;

Things parse_datastream(std::istream& data_stream)
{
    Things data;

    std::string line;
    for (;std::getline(data_stream, line);)
    {   
        std::istringstream v(line);
    }
    
    return data;
}

}

std::size_t ${MODULE}lib::part1_solve(std::istream& data_stream)
{
    auto things = parse_datastream(data_stream);
    return 0;
}

std::size_t ${MODULE}lib::part2_solve(std::istream& data_stream)
{
    auto things = parse_datastream(data_stream);
    return 0;
}


EOT

read -r -d '' SRC_HEADER <<-EOT
#ifndef ${MODULEUP}_H
#define ${MODULEUP}_H

#include <string>

int ${MODULE}(const std::string& filename);



#endif
EOT

read -r -d '' SRC_CPP <<-EOT
#include "${MODULE}.h"
#include "${MODULE}_lib.h"
#include <iostream>
#include <fstream>

using namespace ${MODULE}lib;

int ${MODULE}(const std::string& filename)
{
    std::ifstream datafile(filename);
    if(!datafile)
    {
        std::cout << "Error opening input file" << std::endl;
        return -1;
    }
    std::cout << "Day ${DAY_NUMBER} Part 1 Solution= " << part1_solve(datafile) << std::endl;

    std::ifstream datafile2(filename);
    std::cout << "Day ${DAY_NUMBER} Part 2 Solution= " << part2_solve(datafile2) << std::endl;

    return -1;
}
EOT

read -r -d '' TEST_HEADER <<-EOT
#ifndef ${MODULEUP}_TEST_H
#define ${MODULEUP}_TEST_H

namespace ${MODULE}test {

bool ${MODULE}_test();

}

#endif
EOT

read -r -d '' TEST_CPP <<-EOT
#include "${MODULE}_test.h"
#include "${MODULE}_lib.h"
#include "test_runner.h"
#include <sstream>
#include <fstream>
#include <string>

using namespace ${MODULE}lib;
using namespace ${MODULE}test;

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
    std::string data_file_name = "./data/day${DAY_NUMBER}_data.txt";

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

bool ${MODULE}test::${MODULE}_test()
{
   test_runner::Tests tests = {
        {"test_sample_data", test_sample_data}
        ,{"test_sample_data_part2", test_sample_data_part2}
        ,{"test_data", test_data}
    };

    return test_runner::run_tests("${MODULE}_test", tests);
}

EOT

echo "${LIB_HEADER}" > "./library/${MODULE}_lib.h"
echo "${LIB_CPP}" > "./library/${MODULE}_lib.cpp"
echo "${SRC_HEADER}" > "./src/${MODULE}.h"
echo "${SRC_CPP}" > "./src/${MODULE}.cpp"
echo "${TEST_HEADER}" > "./src_test/${MODULE}_test.h"
echo "${TEST_CPP}" > "./src_test/${MODULE}_test.cpp"


INCLUDE_MARKER="//MAKEMODULE INCLUDE MARKER. DO NOT DELETE"
LIST_MARKER="//MAKEMODULE LIST MARKER. DO NOT DELETE"

INCLUDE_ITEM="\#include \"${MODULE}_test\.h\""
LIST_ITEM=",{\"${MODULE}_test\", ${MODULE}test::${MODULE}_test}"

# the goofiness with the $ and \\\n is to get a newline in the replacement text
sed -E -i '' -e "s~${INCLUDE_MARKER}~${INCLUDE_ITEM}"$'\\\n'"&~g" ./src_test/test_main.cpp
sed -E -i '' -e "s~${LIST_MARKER}~${LIST_ITEM}"$'\\\n'"        &~g"  ./src_test/test_main.cpp

# ,{999, day02};
DAY_MAP_ITEM=",{${DAY_NUMBER}, ${MODULE}}"
MAIN_INCLUDE_ITEM="\#include \"${MODULE}\.h\""


sed -E -i '' -e "s~${INCLUDE_MARKER}~${MAIN_INCLUDE_ITEM}"$'\\\n'"&~g" ./src/main.cpp
sed -E -i '' -e "s~${LIST_MARKER}~${DAY_MAP_ITEM}"$'\\\n'"    &~g"  ./src/main.cpp
