#include <gtest/gtest.h>

#include <numeric>
#include <sstream>
#include <string>
#include <type_traits>

#include "../src/Earley.hpp"

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}