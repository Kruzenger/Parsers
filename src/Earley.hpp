#pragma once
#include "Grammar.hpp"

class EarleyParser {
  friend Grammar_CF;
  class Situation;

 public:
  EarleyParser();
  EarleyParser(Grammar_CF& grammar);

  bool Parse(std::string& word);
  bool Parse(const char* input_word);

 private:
  std::vector<std::vector<EarleyParser::Situation>> Initialise(
      std::string& word);
  void Scan(size_t k, size_t j, std::string& word,
            std::vector<std::vector<EarleyParser::Situation>>& S);
  void Predict(size_t k, size_t j,
               std::vector<std::vector<EarleyParser::Situation>>& S);
  void Complete(size_t k, size_t j,
                std::vector<std::vector<EarleyParser::Situation>>& S);

  Grammar_CF grammar_;
  Grammar_CF::Rule start_rule_;
};

class EarleyParser::Situation {
  friend EarleyParser;

 public:
  Situation();
  Situation(Grammar_CF::Rule& rule, size_t dot_position = 0,
            size_t return_dot_position = 0);

  Grammar_CF::State& Next();

  bool operator==(const Situation& other) const;

 private:
  Grammar_CF::Rule rule_;
  size_t dot_position_ = 0;
  size_t return_position_ = 0;
};
