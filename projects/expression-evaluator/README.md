# expression-evaluator

A small arithmetic expression evaluator written in C++17, built in stages:

1. **Lexer** – turns a string such as `3 + 4.5 * (2 - 1)` into tokens.
2. **Parser** – converts tokens to Reverse Polish Notation with the
   shunting-yard algorithm *(planned)*.
3. **Evaluator** – computes the RPN result *(planned)*.

No external dependencies; only the standard library.

## Build & test

```sh
make test      # builds build/tests and runs it
make clean
```

Or without make:

```sh
g++ -std=c++17 -Wall -Wextra -Isrc tests/tests.cpp src/lexer.cpp -o tests_bin && ./tests_bin
```

## Layout

```
src/lexer.hpp, src/lexer.cpp   tokenizer
tests/tests.cpp                minimal self-contained test runner
```
