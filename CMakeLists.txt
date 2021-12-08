# Requires Cmake 3.20 now
cmake_minimum_required(VERSION 3.17)

# assumes the gcc g++-11 is installed
# note that some versions of macos brew do NOT automatically put these in /usr/local/bin
# check `brew --prefix` to see where it puts them and make links as needed
set(CMAKE_CXX_COMPILER "/usr/local/bin/g++-11")

# Project name and a few useful settings. Other commands can pick up the results
project(
  aoc2021
  VERSION 0.1
  DESCRIPTION "Advent of Code 2021"
  LANGUAGES CXX)


# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

  # Optionally set things like CMAKE_CXX_STANDARD, CMAKE_POSITION_INDEPENDENT_CODE here
  set(CMAKE_CXX_STANDARD 20)


  # Let's ensure -std=c++xx instead of -std=g++xx
  set(CMAKE_CXX_EXTENSIONS OFF)

  add_compile_options(-Wall -Wextra -Wpedantic -Werror)
  add_compile_options(-g -O0)
  add_compile_options(-fcompare-debug-second)

  # Let's nicely support folders in IDEs
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)

  # Testing only available if this is the main app
  # Note this needs to be done in the main CMakeLists
  # since it calls enable_testing, which must be in the
  # main CMakeLists.
  set(CTEST_OUTPUT_ON_FAILURE 1)
  list (APPEND CMAKE_CTEST_ARGUMENTS "-V")
  include(CTest)

  # Docs only available if this is the main app
  find_package(Doxygen)
  if(Doxygen_FOUND)
    add_subdirectory(docs)
  else()
    message(STATUS "Doxygen not found, not building docs")
  endif()
endif()

# FetchContent added in CMake 3.11, downloads during the configure step
include(FetchContent)

# Formatting library
# FetchContent_Declare(
#   fmtlib
#   GIT_REPOSITORY https://github.com/fmtlib/fmt.git
#   GIT_TAG 5.3.0
# )
# FetchContent_MakeAvailable(fmtlib)
# Adds fmt::fmt

# homebrew puts things in different places depending on the system
IF(CMAKE_SYSTEM_NAME MATCHES "Darwin")
    execute_process(COMMAND brew --prefix OUTPUT_VARIABLE HOMEBREW_BASE_FOLDER OUTPUT_STRIP_TRAILING_WHITESPACE)
ELSE()
    message(WARNING "Not sure anything other than APPLE is supported. Good Luck!")
ENDIF()

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/")

# The compiled library code is here
add_subdirectory(src)

# The executable code is here
add_subdirectory(apps)

# Testing only available if this is the main app
# Emergency override MODERN_CMAKE_BUILD_TESTING provided as well
if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING)
   AND BUILD_TESTING)

  add_subdirectory(tests)
endif()
