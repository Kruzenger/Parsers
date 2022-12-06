#pragma once
#include "Grammar.hpp"

class EarleyParser {
  class Situation;

 public:
  void Initialise();
  void Parse();

 private:
  void Scan();
  void Predict();
  void Complete();

  Grammar_CF grammar_;
};

class EarleyParser::Situation {
 public:
  Situation();

 private:
  Grammar_CF::Rule rule_;
  size_t dot_position_ = 0;
  size_t return_dot_position_ = 0;
};
