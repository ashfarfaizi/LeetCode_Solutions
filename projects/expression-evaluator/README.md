# expression-evaluator

A small arithmetic expression evaluator written in C++17, built in stages:

1. **Lexer** – turns a string such as `3 + 4.5 * (2 - 1)` into tokens.
2. **Parser** – converts tokens to Reverse Polish Notation with the
   shunting-yard algorithm (`+ -` < `* /` < `^`, with `^` right-associative).
3. **Evaluator** – computes the RPN result with a value stack and reports
   errors such as division by zero.

```cpp
#include "evaluator.hpp"
double x = expr::evaluate("(3 + 4) * 2 ^ 2");  // 28
```

No external dependencies; only the standard library.

## Build & test

```sh
make test      # builds build/tests and runs it
make clean
```

Or without make:

```sh
g++ -std=c++17 -Wall -Wextra -Isrc tests/tests.cpp src/lexer.cpp src/parser.cpp src/evaluator.cpp -o tests_bin && ./tests_bin
```

## Layout

```
src/lexer.hpp, src/lexer.cpp   tokenizer
src/parser.hpp, src/parser.cpp shunting-yard infix -> RPN
src/evaluator.hpp/.cpp         RPN evaluation + evaluate() helper
tests/tests.cpp                minimal self-contained test runner
```
