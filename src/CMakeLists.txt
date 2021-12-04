# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

set(HEADER_LIST
"${PROJECT_SOURCE_DIR}/include/aoc/day2.h"
"${PROJECT_SOURCE_DIR}/include/aoc/day2_lib.h"
    "${PROJECT_SOURCE_DIR}/include/aoc/day01_lib.h"
    "${PROJECT_SOURCE_DIR}/include/aoc/day01.h"
)

# These can be multiple libraries built here
# Just add sets of these three commands
add_library(aoc_library
"${PROJECT_SOURCE_DIR}/src/aoc/day2.cpp"
"${PROJECT_SOURCE_DIR}/src/aoc/day2_lib.cpp"
            "${PROJECT_SOURCE_DIR}/src/aoc/day01_lib.cpp"
            "${PROJECT_SOURCE_DIR}/src/aoc/day01.cpp"
            ${HEADER_LIST})
target_include_directories(aoc_library PUBLIC ../include)
target_compile_features(aoc_library PUBLIC cxx_std_20)


add_library(aoc_core
        "${PROJECT_SOURCE_DIR}/src/library/dummy.cpp"
        "${PROJECT_SOURCE_DIR}/src/library/chrono_helpers.cpp"
            ${HEADER_LIST})
target_include_directories(aoc_core PUBLIC ../include)
target_compile_features(aoc_core PUBLIC cxx_std_20)

# IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})
