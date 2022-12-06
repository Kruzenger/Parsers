#include <gtest/gtest.h>

#include <numeric>
#include <sstream>
#include <string>
#include <type_traits>

#include "../src/Earley.hpp"

TEST(ContextFreeGrammar, Constructor) {
  try {
    Grammar_CF grammar("../tests/test_constructor_1.txt");
  } catch (std::logic_error ex) {
    std::cout << ex.what() << '\n';
  }
}

TEST(ContextFreeGrammar, ConstructorExceptions) {
  try {
    Grammar_CF grammar("../tests/test_constructor_1");
  } catch (std::logic_error ex) {
    EXPECT_EQ(std::string(ex.what()),
              "Failed to open file: ../tests/test_constructor_1");
  }

  try {
    Grammar_CF grammar("../tests/test_constructor_2.txt");
  } catch (std::logic_error ex) {
    EXPECT_EQ(std::string(ex.what()),
              "There no starting Nonterminal S in grammatic in file: "
              "../tests/test_constructor_2.txt");
  }

  try {
    Grammar_CF grammar("../tests/test_constructor_3.txt");
  } catch (std::logic_error ex) {
    EXPECT_EQ(std::string(ex.what()),
              "Invalid Format of rule: no such states in grammatic in file: "
              "../tests/test_constructor_3.txt");
  }
}

TEST(EarleyParser, Consructor) {}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}