# Parsers

Formal languages practics

Hello everyone! Today I want to tell you how to use my realisation of Earley Parser:

So, first of all My project contains some tests. You can run them, by cloning googletests in main folder with Parser, and build the project with CMake. You can find basic CMakeLists.txt in main folder as well.

If you want to compile Parser without tests, use command ```g++ -g ./src/main.cpp ./src/Earley.cpp ./src/Grammar.cpp -o execute_me.out``` and now you can find executable file named ```execute_me.out```. Now you almost ready to have fun. All that's left - is to write your own grammatic in file your_test. You can find it in directory ```tests/```

There are how to input your grammatic:

* N - number of symbols
* N lines in format: S T, where S - symbol, T = 1 if this symbol is Terminal, 0 if not.
* M - number of Rules
* M lines in format: N a, where N - nonterminal, a - string of terminals and nonterminals

Example:

```
3
S 0
a 1
b 1
2
S aSbS
S 0
```
