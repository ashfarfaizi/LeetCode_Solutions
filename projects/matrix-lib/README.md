# matrix-lib

A small header-only C++17 dense matrix library (`double` elements, row-major
storage). Meant for small linear-algebra jobs and as a readable reference
implementation rather than a BLAS replacement.

```cpp
#include "matrix.hpp"

mat::Matrix a{{1, 2}, {3, 4}};
mat::Matrix b(2, 2, 1.0);        // 2x2 filled with 1.0
auto c = a + b * 3.0;            // element-wise ops and scalar scaling
double x = c(1, 0);              // unchecked access
double y = c.at(1, 0);           // bounds-checked, throws std::out_of_range
c.approxEqual(a, 1e-9);          // tolerance comparison for float results
```

Matrix product and transpose:

```cpp
mat::Matrix p = a * b;           // requires a.cols() == b.rows()
p *= a;                          // in-place product
mat::Matrix t = p.transpose();

auto id = mat::Matrix::identity(3);
mat::Matrix fib{{1, 1}, {1, 0}};
fib.pow(10)(0, 1);               // 55: fast exponentiation by squaring
a.trace();                       // sum of the diagonal (square only)
```

Shape mismatches throw `std::invalid_argument`.

## Build and test

```sh
make test        # builds build/tests with -Wall -Wextra and runs it
make clean
```

Or without make:

```sh
g++ -std=c++17 -Wall -Wextra -Iinclude tests/tests.cpp -o tests_bin && ./tests_bin
```
