#include "Earley.hpp"

EarleyParser::Situation::Situation() { rule_ = Grammar_CF::Rule(); }

EarleyParser::Situation::Situation(Grammar_CF::Rule& rule, size_t dot_position,
                                   size_t return_dot_position) {
  rule_ = rule;
  dot_position_ = dot_position;
  return_position_ = return_dot_position;
}

bool EarleyParser::Situation::operator==(const Situation& other) const {
  return dot_position_ == other.dot_position_ &&
         return_position_ == other.return_position_ && rule_ == other.rule_;
}

Grammar_CF::State& EarleyParser::Situation::Next() {
  return rule_[dot_position_];
}

/////////////////////////////////////////////////

EarleyParser::EarleyParser() {}

EarleyParser::EarleyParser(Grammar_CF& grammar) {
  start_rule_ = Grammar_CF::Rule(0, {'S'});
  grammar_ = grammar;
}

std::vector<std::vector<EarleyParser::Situation>> EarleyParser::Initialise(
    std::string& word) {
  std::vector<std::vector<Situation>> S(word.size() + 1,
                                        std::vector<Situation>());
  S[0].push_back(Situation(start_rule_, 0, 0));

  return S;
}

bool EarleyParser::Parse(std::string& word) {
  std::vector<std::vector<EarleyParser::Situation>> S = Initialise(word);
  for (size_t k = 0; k <= word.size(); ++k) {
    for (size_t j = 0; j < S[k].size(); ++j) {
      if (S[k][j].dot_position_ != S[k][j].rule_.lead_states_.size()) {
        if (S[k][j].Next().IsTerminal()) {
          Scan(k, j, word, S);
        } else {
          Predict(k, j, S);
        }
      } else {
        if (S[k][j] == Situation(start_rule_, 1, 0)) {
          if (k == word.size()) {
            return true;
          }
        } else {
          Complete(k, j, S);
        }
      }
    }
  }

  return false;
}

bool EarleyParser::Parse(const char* input_word) {
  std::string word(input_word);
  std::vector<std::vector<EarleyParser::Situation>> S = Initialise(word);
  for (size_t k = 0; k <= word.size(); ++k) {
    for (size_t j = 0; j < S[k].size(); ++j) {
      if (S[k][j].dot_position_ != S[k][j].rule_.lead_states_.size()) {
        if (S[k][j].Next().IsTerminal()) {
          Scan(k, j, word, S);
        } else {
          Predict(k, j, S);
        }
      } else {
        if (S[k][j] == Situation(start_rule_, 1, 0)) {
          if (k == word.size()) {
            return true;
          }
        } else {
          Complete(k, j, S);
        }
      }
    }
  }

  return false;
}

void EarleyParser::Scan(size_t k, size_t j, std::string& word,
                        std::vector<std::vector<EarleyParser::Situation>>& S) {
  if (S[k][j].Next() == '0') {
    S[k].push_back(Situation(S[k][j].rule_, S[k][j].dot_position_ + 1,
                             S[k][j].return_position_));
  } else if (S[k][j].Next() == word[k] && k < word.size()) {
    S[k + 1].push_back(Situation(S[k][j].rule_, S[k][j].dot_position_ + 1,
                                 S[k][j].return_position_));
  }
}

void EarleyParser::Predict(
    size_t k, size_t j, std::vector<std::vector<EarleyParser::Situation>>& S) {
  for (Grammar_CF::Rule rule : grammar_.R_) {
    if (rule.start_state_ == S[k][j].Next()) {
      Situation situation(rule, 0, k);
      bool add = true;
      for (std::vector<EarleyParser::Situation>::iterator it = S[k].begin();
           it < S[k].end(); ++it) {
        if (*it == situation) {
          add = false;
          break;
        }
      }
      if (add) {
        S[k].push_back(situation);
      }
    }
  }
}

void EarleyParser::Complete(
    size_t k, size_t j, std::vector<std::vector<EarleyParser::Situation>>& S) {
  size_t size = S[S[k][j].return_position_].size();
  for (size_t g = 0; g < size; ++g) {
    if (S[S[k][j].return_position_][g].dot_position_ !=
            S[S[k][j].return_position_][g].rule_.lead_states_.size() &&
        S[S[k][j].return_position_][g].Next() == S[k][j].rule_.start_state_) {
      S[k].push_back(
          Situation(S[S[k][j].return_position_][g].rule_,
                    S[S[k][j].return_position_][g].dot_position_ + 1,
                    S[S[k][j].return_position_][g].return_position_));
    }
  }
}

// int main() {
//   try {
//     Grammar_CF grammar("../tests/test_constructor_1.txt");
//     EarleyParser parser(grammar);
//     std::cout << parser.Parse("ab") << '\n';
//   } catch (std::logic_error ex) {
//     std::cout << ex.what() << '\n';
//   }
// }
