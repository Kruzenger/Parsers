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

  friend std::istream& operator>>(std::istream& stream, State& obj);

 private:
  std::map<char, State> N_;
  std::map<char, State> E_;
  std::map<char, Rule> R_;
};

class Grammar_CF::State {
  friend Grammar_CF;

 public:
  State();
  State(const char new_symbol, bool is_terminal = false);

  friend std::istream& operator>>(std::istream& stream, State& obj);

  bool IsTerminal();
  bool operator==(const State& other) const;
  bool operator==(const char& other) const;

 private:
  char symbol_ = 0;
  bool is_terminal_ = false;
};

Grammar_CF::State::State() {}

Grammar_CF::State::State(const char new_symbol, bool is_terminal)
    : symbol_(new_symbol), is_terminal_(is_terminal) {}

bool Grammar_CF::State::operator==(const State& other) const {
  return symbol_ == other.symbol_ && is_terminal_ == other.is_terminal_;
}

bool Grammar_CF::State::operator==(const char& other) const {
  return symbol_ == other;
}

bool Grammar_CF::State::IsTerminal() { return is_terminal_; }

std::istream& operator>>(std::istream& stream, Grammar_CF::State& obj) {
  stream >> obj.symbol_ >> obj.is_terminal_;
  return stream;
}

///////////////////////////////////////////////////

class Grammar_CF::Rule {
  friend Grammar_CF;

 public:
  Rule();
  Rule(const State& start_state);
  Rule(const State& start_state,
       const std::vector<Grammar_CF::State>& lead_states);

 private:
  Grammar_CF::State start_state_;
  std::vector<Grammar_CF::State> lead_states_;
};

Grammar_CF::Rule::Rule() {}
Grammar_CF::Rule::Rule(const State& start_state) : start_state_(start_state) {}
Grammar_CF::Rule::Rule(const State& start_state,
                       const std::vector<Grammar_CF::State>& lead_states)
    : start_state_(start_state), lead_states_(lead_states) {}

///////////////////////////////////////////////////

Grammar_CF::Grammar_CF() {}

Grammar_CF::Grammar_CF(std::string file_name) {
  std::ifstream input(file_name);
  if (!input) {
    throw std::logic_error("Failed to open file: " + file_name);
  }
  size_t states_size = 0;
  input >> states_size;
  for (size_t i = 0; i < states_size; ++i) {
    State state;
    input >> state;
    if (state.IsTerminal()) {
      E_.insert({state.symbol_, state});
    } else {
      N_.insert({state.symbol_, state});
    }
  }

  if (N_.find('S') == N_.end()) {
    throw std::logic_error(
        "There no starting Nonterminal S in grammatic in file: " + file_name);
  }

  size_t rules_size = 0;
  input >> rules_size;
  for (size_t i = 0; i < rules_size; ++i) {
    Rule rule;
    char start_symbol = 0;
    input >> start_symbol;
    if (N_.find(start_symbol) != N_.end()) {
      continue;  // Skip inaccessible rule
    }
    rule.start_state_ = N_[start_symbol];
    std::string lead_symbols;
    input >> lead_symbols;
    for (size_t i = 0; i < lead_symbols.size(); ++i) {
      if (N_.find(lead_symbols[i]) != N_.end()) {
        rule.lead_states_.push_back(N_[lead_symbols[i]]);
      } else if (E_.find(lead_symbols[i]) != E_.end()) {
        rule.lead_states_.push_back(E_[lead_symbols[i]]);
      } else {
        throw std::logic_error(
            "Invalid Format of rule: no such states in grammatic in file: " +
            file_name);
      }
    }
  }
}
