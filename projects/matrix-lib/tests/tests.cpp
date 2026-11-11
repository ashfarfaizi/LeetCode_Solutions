// Minimal self-contained test runner for matrix-lib.
#include "matrix.hpp"

#include <cmath>
#include <iostream>
#include <sstream>
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

static void testProductAndTranspose() {
    Matrix a{{1, 2, 3}, {4, 5, 6}};
    Matrix b{{7, 8}, {9, 10}, {11, 12}};
    CHECK((a * b == Matrix{{58, 64}, {139, 154}}));
    CHECK((b * a == Matrix{{39, 54, 69}, {49, 68, 87}, {59, 82, 105}}));
    CHECK_THROWS(a * a, std::invalid_argument);

    CHECK((a.transpose() == Matrix{{1, 4}, {2, 5}, {3, 6}}));
    CHECK(a.transpose().transpose() == a);
    // (AB)^T == B^T A^T
    CHECK((a * b).transpose() == b.transpose() * a.transpose());

    Matrix c{{1, 1}, {0, 1}};
    c *= Matrix{{1, 0}, {1, 1}};
    CHECK((c == Matrix{{2, 1}, {1, 1}}));
}

static void testIdentityPowTrace() {
    Matrix i3 = Matrix::identity(3);
    CHECK(i3.trace() == 3.0);
    Matrix a{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    CHECK(a * i3 == a && i3 * a == a);
    CHECK(a.trace() == 15.0);

    // Fibonacci via [[1,1],[1,0]]^n = [[F(n+1),F(n)],[F(n),F(n-1)]]
    Matrix fib{{1, 1}, {1, 0}};
    CHECK(fib.pow(0) == Matrix::identity(2));
    CHECK(fib.pow(1) == fib);
    CHECK(fib.pow(10)(0, 1) == 55.0);
    CHECK(fib.pow(30)(0, 1) == 832040.0);
    CHECK(a.pow(3) == a * a * a);

    CHECK_THROWS(Matrix(2, 3).pow(2), std::invalid_argument);
    CHECK_THROWS(Matrix(2, 3).trace(), std::invalid_argument);
}

static bool near(double a, double b, double eps = 1e-9) { return std::fabs(a - b) <= eps; }

static void testDeterminant() {
    CHECK(near(Matrix{{4}}.determinant(), 4));
    CHECK(near((Matrix{{1, 2}, {3, 4}}).determinant(), -2));
    CHECK(near((Matrix{{6, 1, 1}, {4, -2, 5}, {2, 8, 7}}).determinant(), -306));
    // Needs a row swap: the first pivot is zero.
    CHECK(near((Matrix{{0, 1}, {1, 0}}).determinant(), -1));
    CHECK(near((Matrix{{0, 2, 1}, {1, 0, 0}, {0, 0, 3}}).determinant(), -6));
    // Singular: linearly dependent rows.
    CHECK(near((Matrix{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}).determinant(), 0, 1e-9));
    CHECK(Matrix::identity(5).determinant() == 1.0);
    // det(AB) == det(A) det(B)
    Matrix a{{2, -1, 0}, {1, 3, 4}, {0, 5, -2}};
    Matrix b{{1, 0, 2}, {-1, 1, 0}, {3, 2, 1}};
    CHECK(near((a * b).determinant(), a.determinant() * b.determinant(), 1e-7));
    CHECK_THROWS(Matrix(2, 3).determinant(), std::invalid_argument);

    Matrix s{{1, 2}, {3, 4}, {5, 6}};
    s.swapRows(0, 2);
    CHECK((s == Matrix{{5, 6}, {3, 4}, {1, 2}}));
    CHECK_THROWS(s.swapRows(0, 3), std::out_of_range);
}

static void testInverse() {
    Matrix a{{4, 7}, {2, 6}};
    CHECK(a.inverse().approxEqual(Matrix{{0.6, -0.7}, {-0.2, 0.4}}));
    CHECK((a * a.inverse()).approxEqual(Matrix::identity(2)));

    // Zero leading pivot forces a row swap.
    Matrix b{{0, 2, 1}, {1, 0, 0}, {0, 0, 3}};
    CHECK((b * b.inverse()).approxEqual(Matrix::identity(3)));
    CHECK((b.inverse() * b).approxEqual(Matrix::identity(3)));

    Matrix c{{2, -1, 0}, {-1, 2, -1}, {0, -1, 2}};
    CHECK(c.inverse().approxEqual(Matrix{{0.75, 0.5, 0.25}, {0.5, 1, 0.5}, {0.25, 0.5, 0.75}}));
    CHECK(c.inverse().inverse().approxEqual(c));
    CHECK(near(c.inverse().determinant(), 1.0 / c.determinant()));

    CHECK_THROWS((Matrix{{1, 2}, {2, 4}}).inverse(), std::domain_error);
    CHECK_THROWS(Matrix(2, 3).inverse(), std::invalid_argument);
}

static void testSolveAndPrint() {
    // 2x + y - z = 8, -3x - y + 2z = -11, -2x + y + 2z = -3  ->  (2, 3, -1)
    Matrix a{{2, 1, -1}, {-3, -1, 2}, {-2, 1, 2}};
    Matrix b{{8}, {-11}, {-3}};
    CHECK(a.solve(b).approxEqual(Matrix{{2}, {3}, {-1}}));

    // Several right-hand sides at once: solving against I gives the inverse.
    CHECK(a.solve(Matrix::identity(3)).approxEqual(a.inverse()));

    Matrix swapNeeded{{0, 1}, {1, 1}};
    CHECK(swapNeeded.solve(Matrix{{2}, {5}}).approxEqual(Matrix{{3}, {2}}));

    CHECK_THROWS((Matrix{{1, 2}, {2, 4}}).solve(Matrix{{1}, {2}}), std::domain_error);
    CHECK_THROWS(a.solve(Matrix(2, 1)), std::invalid_argument);

    std::ostringstream os;
    os << Matrix{{1, 2.5}, {-3, 0}};
    CHECK(os.str() == "[1, 2.5]\n[-3, 0]\n");
}

int main() {
    testConstruction();
    testArithmetic();
    testApproxEqual();
    testProductAndTranspose();
    testIdentityPowTrace();
    testDeterminant();
    testInverse();
    testSolveAndPrint();
    std::cout << (checks - failures) << "/" << checks << " checks passed\n";
    return failures == 0 ? 0 : 1;
}
