# expression-evaluator

A small arithmetic expression evaluator written in C++17, built in stages:

1. **Lexer** – turns a string such as `3 + 4.5 * (2 - 1)` into tokens.
2. **Parser** – converts tokens to Reverse Polish Notation with the
   shunting-yard algorithm (`+ -` < `* /` < unary `-` < `^`, with `^`
   right-associative, so `-2^2 = -4` and `2^-1 = 0.5`).
3. **Evaluator** – computes the RPN result with a value stack and reports
   errors such as division by zero.

```cpp
#include "evaluator.hpp"
double x = expr::evaluate("(3 + 4) * 2 ^ 2");  // 28
```

No external dependencies; only the standard library.

## Build & test

```sh
make           # builds build/calc and runs the tests
make test      # builds build/tests and runs it
make clean
```

## Usage

```sh
$ ./build/calc "2 * (3 + 4)"
14
$ ./build/calc
> -2 ^ 2
-4
> 1 / 0
eval error: division by zero
> exit
```

Errors go to stderr; in one-shot mode the exit status is 1 on error.

Or without make:

```sh
g++ -std=c++17 -Wall -Wextra -Isrc tests/tests.cpp src/lexer.cpp src/parser.cpp src/evaluator.cpp -o tests_bin && ./tests_bin
```

## Layout

```
src/lexer.hpp, src/lexer.cpp   tokenizer
src/parser.hpp, src/parser.cpp shunting-yard infix -> RPN
src/evaluator.hpp/.cpp         RPN evaluation + evaluate() helper
src/main.cpp                   CLI: one-shot or interactive REPL
tests/tests.cpp                minimal self-contained test runner
```
