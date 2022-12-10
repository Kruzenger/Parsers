#include "./Earley.hpp"

int main() {
  Grammar_CF grammar("../tests/your_test.txt");
  EarleyParser parser(grammar);

  std::string word;
  std::cin >> word;

  while (word[0] != EOF) {
    std::cout << (parser.Parse(word) ? "YES" : "NO") << std::endl;
    std::cin >> word;
  }

  return 0;
}