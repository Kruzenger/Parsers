#pragma once

#include <fstream>
#include <iostream>
#include <map>
#include <stdexcept>
#include <vector>

class Grammar_CF {
  friend class EarleyParser;

  class State;
  class Rule;

 public:
  Grammar_CF();
  Grammar_CF(std::string file_name);

  friend bool operator==(const Rule& lhs, const Rule& rhs);
  friend bool operator==(const State& lhs, const State& rhs);
  friend bool operator==(const State& lhs, const char& rhs);

  friend std::istream& operator>>(std::istream& stream, State& obj);

 private:
  std::map<char, State> N_;
  std::map<char, State> E_;
  std::vector<Rule> R_;
};

class Grammar_CF::State {
  friend Grammar_CF;

 public:
  State();
  State(const char new_symbol, bool is_terminal = false);

  friend std::istream& operator>>(std::istream& stream, State& obj);

  bool IsTerminal();
  friend bool operator==(const State& lhs, const State& rhs);
  friend bool operator==(const State& lhs, const char& rhs);

 private:
  char symbol_ = 0;
  bool is_terminal_ = false;
};

///////////////////////////////////////////////////

class Grammar_CF::Rule {
  friend Grammar_CF;
  friend class EarleyParser;

 public:
  Rule();
  Rule(const State& start_state);
  Rule(const State& start_state,
       const std::vector<Grammar_CF::State>& lead_states);

  friend bool operator==(const Rule& lhs, const Rule& rhs);

  Grammar_CF::State& operator[](size_t index);

 private:
  Grammar_CF::State start_state_;
  std::vector<Grammar_CF::State> lead_states_;
};

///////////////////////////////////////////////////
