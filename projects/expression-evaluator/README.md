# expression-evaluator

A small arithmetic expression evaluator written in C++17, built in stages:

1. **Lexer** – turns a string such as `3 + 4.5 * (2 - pi)` into number,
   operator, parenthesis and identifier tokens. Numbers may be written in
   scientific notation (`1e3`, `2.5E-4`).
2. **Parser** – converts tokens to Reverse Polish Notation with the
   shunting-yard algorithm (`+ -` < `* / %` < unary `-` < `^`, with `^`
   right-associative, so `-2^2 = -4` and `2^-1 = 0.5`). The comparisons
   `< <= > >= == !=` bind loosest of all and yield `1` (true) or `0`
   (false), so `1 + 1 == 2` is `1` and `(x > 0) * x` clamps at zero.
   Postfix `!` is the factorial and binds tightest, so `2^3! = 64` and
   `-3! = -6`; it accepts non-negative integers up to `170`. Note that
   `3!=6` lexes as `3 != 6`; write `(3!) == 6` to compare a factorial.
3. **Evaluator** – computes the RPN result with a value stack and reports
   errors such as division or modulo by zero. `%` is the
   floating-point remainder (`fmod`), so `-7 % 3 = -1` and `5.5 % 2 = 1.5`.

```cpp
#include "evaluator.hpp"
double x = expr::evaluate("(3 + 4) * 2 ^ 2");  // 28
```

The constants `pi` and `e` are built in, along with the one-argument
functions `sqrt cbrt abs sign exp ln log10 sin cos tan floor ceil round
trunc` (angles in radians), the two-argument `pow hypot atan2` and
`gcd lcm` (integers only, sign ignored), and the variadic
`min` / `max`, e.g. `max(1, hypot(3, 4), 2)` is `5`. Passing the wrong
number of arguments is an eval error. Domain errors such as `sqrt(-1)` or `ln(0)` are
reported as eval errors rather than returning NaN.

Variables live in an `expr::Environment` (a `std::map<std::string, double>`)
and are set with `name = expression`:

```cpp
expr::Environment env;
expr::evaluate("r = 2", env);
double area = expr::evaluate("pi * r ^ 2", env);  // 12.566...
```

A failed assignment (e.g. `x = 1 / 0`) leaves the previous value in place,
and `pi` / `e` cannot be reassigned.

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
> r = 2
2
> pi * r ^ 2
12.5664
> ans / pi
4
> vars
ans = 4
r = 2
> del r
> vars
ans = 4
> 1 / 0
eval error: division by zero
> exit
```

To see how an expression is parsed, print its RPN form instead:

```sh
$ ./build/calc --rpn "-max(1, 2.5) * x"
1 2.5 max/2 neg x *
```

In the REPL, variables persist between lines, `ans` holds the last
successful result, and `vars` lists all bindings. `del x y` removes the
named variables (reporting any that do not exist) and `clear` removes
them all.

Errors go to stderr; in one-shot mode the exit status is 1 on error.

Or without make:

```sh
g++ -std=c++17 -Wall -Wextra -Isrc tests/tests.cpp src/lexer.cpp src/parser.cpp src/evaluator.cpp -o tests_bin && ./tests_bin
```

## Layout

```
src/lexer.hpp, src/lexer.cpp   tokenizer
src/parser.hpp, src/parser.cpp shunting-yard infix -> RPN, rpnToString()
src/evaluator.hpp/.cpp         RPN evaluation + evaluate() helper
src/main.cpp                   CLI: one-shot or REPL with variables and ans
tests/tests.cpp                minimal self-contained test runner
```
