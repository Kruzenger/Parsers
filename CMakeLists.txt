cmake_minimum_required(VERSION 3.12) # version can be different

project(my_cpp_project) #name of your project

set(src ${CMAKE_SOURCE_DIR})

add_subdirectory(.gitignore/googletest) # add googletest subdirectory

include_directories(googletest/include) # this is so we can #include <gtest/gtest.h>

add_executable(tests ./tests/tests_main.cpp ../src/Earley.cpp ../src/Grammar.cpp) # add this executable

target_link_libraries(tests PRIVATE gtest) # link google test to this executable