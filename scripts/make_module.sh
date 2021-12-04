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
FOLDER="aoc"

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
#include "${FOLDER}/${MODULE}_lib.h"

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
#include "${FOLDER}/${MODULE}.h"
#include "${FOLDER}/${MODULE}_lib.h"
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

}

#endif
EOT

read -r -d '' TEST_CPP <<-EOT
#include "gtest/gtest.h"

#include "${MODULE}_test.h"
#include <${FOLDER}/${MODULE}_lib.h>

#include <sstream>
#include <fstream>
#include <string>

using namespace ${MODULE}lib;
using namespace ${MODULE}test;

namespace {

std::string sample_data_1 = 
    "xx\n"
    "xx\n"
    ;

std::string sample_data_2 = 
    "xx\n"
    "xx\n"
    ;

TEST( ${MODULE}, test_sample_data ) {
    std::istringstream data_stream(sample_data_1);
    auto p = part1_solve(data_stream);
    EXPECT_EQ(999999999, p);
}

TEST( ${MODULE}, test_sample_data_part2 ) {
    std::istringstream data_stream(sample_data_2);
    auto p = part2_solve(data_stream);
    EXPECT_EQ(999999999, p);
}

TEST( ${MODULE}, test_data_1 ) {
    std::string data_file_name = "../data/${MODULE}_data.txt";
    std::ifstream datafile(data_file_name);
    ASSERT_TRUE(datafile) << "Error opening input file" << std::endl;

    auto p1 = part1_solve(datafile);

    EXPECT_EQ(999999999, p1);
}

TEST( ${MODULE}, test_data_2 )
{
    std::string data_file_name = "../data/${MODULE}_data.txt";
    std::ifstream datafile(data_file_name);
    ASSERT_TRUE(datafile) << "Error opening input file" << std::endl;

    auto p2 = part2_solve(datafile);

    EXPECT_EQ(999999999, p2);
}

}

EOT

echo "${LIB_HEADER}" > "./include/${FOLDER}/${MODULE}_lib.h"
echo "${LIB_CPP}" > "./src/${FOLDER}/${MODULE}_lib.cpp"
echo "${SRC_HEADER}" > "./include/${FOLDER}/${MODULE}.h"
echo "${SRC_CPP}" > "./src/${FOLDER}/${MODULE}.cpp"
echo "${TEST_HEADER}" > "./tests/${MODULE}_test.h"
echo "${TEST_CPP}" > "./tests/${MODULE}_test.cpp"


INCLUDE_MARKER="//MAKEMODULE INCLUDE MARKER. DO NOT DELETE"
LIST_MARKER="//MAKEMODULE LIST MARKER. DO NOT DELETE"

# ,{999, day02};
DAY_MAP_ITEM=",{${DAY_NUMBER}, ${MODULE}}"
MAIN_INCLUDE_ITEM="\#include \"${FOLDER}/${MODULE}\.h\""


sed -E -i '' -e "s~${INCLUDE_MARKER}~${MAIN_INCLUDE_ITEM}"$'\\\n'"&~g" ./apps/main.cpp
sed -E -i '' -e "s~${LIST_MARKER}~${DAY_MAP_ITEM}"$'\\\n'"    &~g"  ./apps/main.cpp


function insert_cmake_items()
{
    local CMAKEFILE="$1"
    local MARKER="$2"
    shift; shift;
    local ITEMS="$@"

    for s in ${ITEMS[@]}; do
        sed -E -i '' -e "s~${MARKER}~&"$'\\\n'"${s}~g" "${CMAKEFILE}"
    done
}

HEADER_MARKER='set\(HEADER_LIST'
HEADER_ITEMS=("\"\${PROJECT_SOURCE_DIR}/include/${FOLDER}/${MODULE}_lib.h\"" \
              "\"\${PROJECT_SOURCE_DIR}/include/${FOLDER}/${MODULE}.h\"" \
)

SOURCE_MARKER="add_library\(${FOLDER}_library"
SOURCE_ITEMS=( "\"\${PROJECT_SOURCE_DIR}/src/${FOLDER}/${MODULE}_lib.cpp\"" \
               "\"\${PROJECT_SOURCE_DIR}/src/${FOLDER}/${MODULE}.cpp\"" \
)

TEST_MARKER="add_executable\(test${FOLDER}"
TEST_ITEMS=( \
    ${MODULE}_test.cpp \
)


insert_cmake_items ./src/CMakeLists.txt "${HEADER_MARKER}" "${HEADER_ITEMS[@]}"
insert_cmake_items ./src/CMakeLists.txt "${SOURCE_MARKER}" "${SOURCE_ITEMS[@]}"
insert_cmake_items ./tests/CMakeLists.txt "${TEST_MARKER}" "${TEST_ITEMS[@]}"
