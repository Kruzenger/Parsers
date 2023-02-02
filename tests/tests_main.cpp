#include <gtest/gtest.h>

#include <numeric>
#include <sstream>
#include <string>
#include <type_traits>

#include "../src/Earley.hpp"

TEST(ContextFreeGrammar, Constructor) {
  EXPECT_NO_THROW(Grammar_CF grammar("../tests/test_constructor_1.txt"));
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

TEST(EarleyParser, Consructor) {
  try {
    Grammar_CF grammar("../tests/test_constructor_1.txt");
    EXPECT_NO_FATAL_FAILURE(EarleyParser parser(grammar));
  } catch (std::logic_error ex) {
    std::cout << ex.what() << '\n';
  }
}

TEST(EarleyParser, SimpleParse) {
  try {
    Grammar_CF grammar("../tests/test_parse_simple.txt");
    EarleyParser parser(grammar);
    EXPECT_TRUE(parser.Parse("aabb"));
    EXPECT_TRUE(parser.Parse("aabbab"));
    EXPECT_TRUE(parser.Parse("aabbababaaabbb"));
    EXPECT_FALSE(parser.Parse("abba"));
    EXPECT_FALSE(parser.Parse("abbababa"));
    EXPECT_FALSE(parser.Parse("aabbbbaaab"));
  } catch (std::logic_error ex) {
    std::cout << ex.what() << '\n';
  }
}

TEST(EarleyParser, ComplexParse) {
  try {
    Grammar_CF grammar("../tests/test_parse_complex.txt");
    EarleyParser parser(grammar);
    EXPECT_TRUE(parser.Parse("aabb"));
    EXPECT_TRUE(parser.Parse("aabbab"));
    EXPECT_TRUE(parser.Parse("aabbababaaabbb"));
    EXPECT_FALSE(parser.Parse("abba"));
    EXPECT_FALSE(parser.Parse("abbababa"));
    EXPECT_FALSE(parser.Parse("aabbbbaaab"));
  } catch (std::logic_error ex) {
    std::cout << ex.what() << '\n';
  }
}

TEST(EarleyParser, ComplexParseString) {
  try {
    Grammar_CF grammar("../tests/test_parse_complex.txt");
    EarleyParser parser(grammar);
    std::string words[6] = {"aabb", "aabbab",   "aabbababaaabbb",
                            "abba", "abbababa", "aabbbbaaab"};
    EXPECT_TRUE(parser.Parse(words[0]));
    EXPECT_TRUE(parser.Parse(words[1]));
    EXPECT_TRUE(parser.Parse(words[2]));
    EXPECT_FALSE(parser.Parse(words[3]));
    EXPECT_FALSE(parser.Parse(words[4]));
    EXPECT_FALSE(parser.Parse(words[5]));
  } catch (std::logic_error ex) {
    std::cout << ex.what() << '\n';
  }
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}