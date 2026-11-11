// Minimal self-contained test runner for matrix-lib.
#include "matrix.hpp"

#include <iostream>
#include <stdexcept>

static int failures = 0;
static int checks = 0;

#define CHECK(cond)                                                          \
    do {                                                                     \
        ++checks;                                                            \
        if (!(cond)) {                                                       \
            ++failures;                                                      \
            std::cerr << __FILE__ << ":" << __LINE__ << ": FAILED: " #cond "\n"; \
        }                                                                    \
    } while (0)

#define CHECK_THROWS(expr, Ex)                                               \
    do {                                                                     \
        bool thrown = false;                                                 \
        try { (void)(expr); } catch (const Ex&) { thrown = true; }           \
        CHECK(thrown && #expr " throws " #Ex);                               \
    } while (0)

using mat::Matrix;

static void testConstruction() {
    Matrix z(2, 3);
    CHECK(z.rows() == 2 && z.cols() == 3);
    CHECK(z(1, 2) == 0.0);
    CHECK(!z.isSquare());

    Matrix m{{1, 2}, {3, 4}};
    CHECK(m.isSquare());
    CHECK(m(0, 1) == 2 && m(1, 0) == 3);
    CHECK(m.at(1, 1) == 4);
    CHECK_THROWS(m.at(2, 0), std::out_of_range);
    CHECK_THROWS((Matrix{{1, 2}, {3}}), std::invalid_argument);
}

static void testArithmetic() {
    Matrix a{{1, 2}, {3, 4}};
    Matrix b{{5, 6}, {7, 8}};
    CHECK((a + b == Matrix{{6, 8}, {10, 12}}));
    CHECK((b - a == Matrix{{4, 4}, {4, 4}}));
    CHECK((a * 2.0 == Matrix{{2, 4}, {6, 8}}));
    CHECK((0.5 * a == Matrix{{0.5, 1}, {1.5, 2}}));
    CHECK((-a == Matrix{{-1, -2}, {-3, -4}}));
    CHECK_THROWS(a + Matrix(2, 3), std::invalid_argument);
}

static void testApproxEqual() {
    Matrix a{{0.1 + 0.2}};
    Matrix b{{0.3}};
    CHECK(a != b);
    CHECK(a.approxEqual(b));
    CHECK(!a.approxEqual(Matrix(1, 2)));
}

int main() {
    testConstruction();
    testArithmetic();
    testApproxEqual();
    std::cout << (checks - failures) << "/" << checks << " checks passed\n";
    return failures == 0 ? 0 : 1;
}
