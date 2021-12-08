# Testing library
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.10.0
)
FetchContent_MakeAvailable(googletest)
# ${gtest_build_include_dirs}

# If you register a test, then ctest and make test will run it.
# You can also run examples and check the output, as well.

# There can be multiple test programs
# Just add sets of these four commands
add_executable(testaoc
day05_test.cpp
day04_test.cpp
day03_test.cpp
day02_test.cpp
               day01_test.cpp
              )
target_compile_features(testaoc PRIVATE cxx_std_20)

target_link_libraries(testaoc
                      PRIVATE
                      gtest_main
                      aoc_library
                    )

add_test(NAME testaoctest COMMAND testaoc)
