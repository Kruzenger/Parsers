#include "Grammar.hpp"

Grammar_CF::State::State() {}

Grammar_CF::State::State(const char new_symbol, bool is_terminal)
    : symbol_(new_symbol), is_terminal_(is_terminal) {}

bool operator==(const Grammar_CF::State& lhs, const Grammar_CF::State& rhs) {
  return lhs.symbol_ == rhs.symbol_ && lhs.is_terminal_ == rhs.is_terminal_;
}

bool operator==(const Grammar_CF::State& lhs, const char& rhs) {
  return lhs.symbol_ == rhs;
}

bool Grammar_CF::State::IsTerminal() { return is_terminal_; }

std::istream& operator>>(std::istream& stream, Grammar_CF::State& obj) {
  stream >> obj.symbol_ >> obj.is_terminal_;
  return stream;
}

///////////////////////////////////////////////////

Grammar_CF::Rule::Rule() {}

Grammar_CF::Rule::Rule(const State& start_state) : start_state_(start_state) {}

Grammar_CF::Rule::Rule(const State& start_state,
                       const std::vector<Grammar_CF::State>& lead_states)
    : start_state_(start_state), lead_states_(lead_states) {}

bool operator==(const Grammar_CF::Rule& lhs, const Grammar_CF::Rule& rhs) {
  return lhs.start_state_ == rhs.start_state_ &&
         lhs.lead_states_ == rhs.lead_states_;
}

Grammar_CF::State& Grammar_CF::Rule::operator[](size_t index) {
  return lead_states_[index];
}

///////////////////////////////////////////////////

Grammar_CF::Grammar_CF() {}

Grammar_CF::Grammar_CF(std::string file_name) {
  std::ifstream input(file_name);
  if (!input) {
    throw std::logic_error("Failed to open file: " + file_name);
  }
  size_t states_size = 0;
  input >> states_size;
  E_.insert({'0', State('0')});
  E_['0'].is_terminal_ = true;
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
    if (N_.find(start_symbol) == N_.end()) {
      continue;
    }
    rule.start_state_ = N_[start_symbol];
    std::string lead_symbols;
    input >> lead_symbols;
    for (size_t j = 0; j < lead_symbols.size(); ++j) {
      if (N_.find(lead_symbols[j]) != N_.end()) {
        rule.lead_states_.push_back(N_[lead_symbols[j]]);
      } else if (E_.find(lead_symbols[j]) != E_.end()) {
        rule.lead_states_.push_back(E_[lead_symbols[j]]);
      } else {
        throw std::logic_error(
            "Invalid Format of rule: no such states in grammatic in file: " +
            file_name);
      }
    }
    R_.push_back(rule);
  }
}
