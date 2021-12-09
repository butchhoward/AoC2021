# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

set(HEADER_LIST
"${PROJECT_SOURCE_DIR}/include/aoc/day08.h"
"${PROJECT_SOURCE_DIR}/include/aoc/day08_lib.h"
"${PROJECT_SOURCE_DIR}/include/aoc/day07.h"
"${PROJECT_SOURCE_DIR}/include/aoc/day07_lib.h"
"${PROJECT_SOURCE_DIR}/include/aoc/day06.h"
"${PROJECT_SOURCE_DIR}/include/aoc/day06_lib.h"
"${PROJECT_SOURCE_DIR}/include/aoc/day05.h"
"${PROJECT_SOURCE_DIR}/include/aoc/day05_lib.h"
"${PROJECT_SOURCE_DIR}/include/aoc/day04.h"
"${PROJECT_SOURCE_DIR}/include/aoc/day04_lib.h"
"${PROJECT_SOURCE_DIR}/include/aoc/day03.h"
"${PROJECT_SOURCE_DIR}/include/aoc/day03_lib.h"
"${PROJECT_SOURCE_DIR}/include/aoc/day02.h"
"${PROJECT_SOURCE_DIR}/include/aoc/day02_lib.h"
    "${PROJECT_SOURCE_DIR}/include/aoc/day01_lib.h"
    "${PROJECT_SOURCE_DIR}/include/aoc/day01.h"
)

# These can be multiple libraries built here
# Just add sets of these three commands
add_library(aoc_library
"${PROJECT_SOURCE_DIR}/src/aoc/day08.cpp"
"${PROJECT_SOURCE_DIR}/src/aoc/day08_lib.cpp"
"${PROJECT_SOURCE_DIR}/src/aoc/day07.cpp"
"${PROJECT_SOURCE_DIR}/src/aoc/day07_lib.cpp"
"${PROJECT_SOURCE_DIR}/src/aoc/day06.cpp"
"${PROJECT_SOURCE_DIR}/src/aoc/day06_lib.cpp"
"${PROJECT_SOURCE_DIR}/src/aoc/day05.cpp"
"${PROJECT_SOURCE_DIR}/src/aoc/day05_lib.cpp"
"${PROJECT_SOURCE_DIR}/src/aoc/day04.cpp"
"${PROJECT_SOURCE_DIR}/src/aoc/day04_lib.cpp"
"${PROJECT_SOURCE_DIR}/src/aoc/day03.cpp"
"${PROJECT_SOURCE_DIR}/src/aoc/day03_lib.cpp"
"${PROJECT_SOURCE_DIR}/src/aoc/day02.cpp"
"${PROJECT_SOURCE_DIR}/src/aoc/day02_lib.cpp"
            "${PROJECT_SOURCE_DIR}/src/aoc/day01_lib.cpp"
            "${PROJECT_SOURCE_DIR}/src/aoc/day01.cpp"
            ${HEADER_LIST})
target_include_directories(aoc_library PUBLIC ../include)
target_compile_features(aoc_library PUBLIC cxx_std_20)


add_library(aoc_core
        "${PROJECT_SOURCE_DIR}/src/library/dummy.cpp"
        "${PROJECT_SOURCE_DIR}/src/library/chrono_helpers.cpp"
        "${PROJECT_SOURCE_DIR}/src/library/parser_helpers.cpp"
            ${HEADER_LIST})
target_include_directories(aoc_core PUBLIC ../include)
target_compile_features(aoc_core PUBLIC cxx_std_20)

# IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})
