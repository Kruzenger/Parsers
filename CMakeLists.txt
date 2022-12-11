cmake_minimum_required(VERSION 3.15)
project(CoverageTest)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 14)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# setup googletest
add_subdirectory(googletest)

# create our library
add_library(Parse STATIC src/Grammar.hpp src/Grammar.cpp src/Earley.hpp src/Earley.cpp)
add_dependencies(Parse gtest gtest_main)

# create the test executable
add_executable(TestParser tests/tests_main.cpp)
target_include_directories(TestParser PRIVATE googletest/googletest)
target_link_libraries(TestParser PRIVATE
Parse gtest gtest_main)
add_dependencies(TestParser Parse gtest gtest_main)

# now for coverage bits
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
if (CMAKE_COMPILER_IS_GNUCXX)
    include(CodeCoverage)
    append_coverage_compiler_flags()

    # we need to turn off optimization for non-skewed coverage reports
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -O0")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")

    # optional excludes - None needed here
    #    set(COVERAGE_EXCLUDES)

    # importantly, set the path to the gcovr executable that you downladed
    set(GCOVR_PATH "/usr/bin/gcovr")
    # Works
    setup_target_for_coverage_gcovr_xml(
            NAME TestParserCoverageXml
            EXECUTABLE TestParser
            DEPENDENCIES TestParser Parse
    )
    # Works
    setup_target_for_coverage_gcovr_html(
            NAME TestParserCoverageHtml
            EXECUTABLE TestParser
            DEPENDENCIES TestParser Parse
    )
    # This one did not work for me:
    setup_target_for_coverage_lcov(
            NAME TestParserCoverageLcov
            EXECUTABLE TestParser
            DEPENDENCIES TestParser Parse
    )
endif ()