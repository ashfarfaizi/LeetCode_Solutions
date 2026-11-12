// matrix-lib: a small header-only dense matrix of doubles.
#pragma once

#include <cmath>
#include <cstddef>
#include <initializer_list>
#include <ostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace mat {

class Matrix {
public:
    Matrix() = default;

    Matrix(std::size_t rows, std::size_t cols, double fill = 0.0)
        : rows_(rows), cols_(cols), data_(rows * cols, fill) {}

    // Row-major literal: Matrix{{1, 2}, {3, 4}}. All rows must be the same length.
    Matrix(std::initializer_list<std::initializer_list<double>> init) {
        rows_ = init.size();
        cols_ = rows_ ? init.begin()->size() : 0;
        data_.reserve(rows_ * cols_);
        for (const auto& row : init) {
            if (row.size() != cols_) throw std::invalid_argument("ragged matrix literal");
            data_.insert(data_.end(), row.begin(), row.end());
        }
    }

    static Matrix identity(std::size_t n) {
        Matrix m(n, n);
        for (std::size_t i = 0; i < n; ++i) m(i, i) = 1.0;
        return m;
    }

    // Places b to the right of a: [a | b]. Row counts must match.
    static Matrix hstack(const Matrix& a, const Matrix& b) {
        if (a.rows_ != b.rows_) throw std::invalid_argument("shape mismatch in hstack");
        Matrix out(a.rows_, a.cols_ + b.cols_);
        for (std::size_t r = 0; r < a.rows_; ++r) {
            for (std::size_t c = 0; c < a.cols_; ++c) out(r, c) = a(r, c);
            for (std::size_t c = 0; c < b.cols_; ++c) out(r, a.cols_ + c) = b(r, c);
        }
        return out;
    }

    // Places b below a. Column counts must match. Row-major storage makes
    // this a plain concatenation of the two data buffers.
    static Matrix vstack(const Matrix& a, const Matrix& b) {
        if (a.cols_ != b.cols_) throw std::invalid_argument("shape mismatch in vstack");
        Matrix out;
        out.rows_ = a.rows_ + b.rows_;
        out.cols_ = a.cols_;
        out.data_.reserve(a.data_.size() + b.data_.size());
        out.data_.insert(out.data_.end(), a.data_.begin(), a.data_.end());
        out.data_.insert(out.data_.end(), b.data_.begin(), b.data_.end());
        return out;
    }

    std::size_t rows() const { return rows_; }
    std::size_t cols() const { return cols_; }
    bool isSquare() const { return rows_ == cols_; }

    double& operator()(std::size_t r, std::size_t c) { return data_[r * cols_ + c]; }
    double operator()(std::size_t r, std::size_t c) const { return data_[r * cols_ + c]; }

    // Bounds-checked access.
    double& at(std::size_t r, std::size_t c) {
        check(r, c);
        return (*this)(r, c);
    }
    double at(std::size_t r, std::size_t c) const {
        check(r, c);
        return (*this)(r, c);
    }

    Matrix& operator+=(const Matrix& o) {
        requireSameShape(o, "+");
        for (std::size_t i = 0; i < data_.size(); ++i) data_[i] += o.data_[i];
        return *this;
    }
    Matrix& operator-=(const Matrix& o) {
        requireSameShape(o, "-");
        for (std::size_t i = 0; i < data_.size(); ++i) data_[i] -= o.data_[i];
        return *this;
    }
    Matrix& operator*=(double k) {
        for (double& x : data_) x *= k;
        return *this;
    }

    friend Matrix operator+(Matrix a, const Matrix& b) { return a += b; }
    friend Matrix operator-(Matrix a, const Matrix& b) { return a -= b; }
    friend Matrix operator*(Matrix a, double k) { return a *= k; }
    friend Matrix operator*(double k, Matrix a) { return a *= k; }
    friend Matrix operator-(Matrix a) { return a *= -1.0; }

    // Matrix product. Uses i-k-j loop order so the inner loop walks both
    // operands row-wise, which is cache-friendly for row-major storage.
    friend Matrix operator*(const Matrix& a, const Matrix& b) {
        if (a.cols_ != b.rows_) throw std::invalid_argument("shape mismatch in matrix product");
        Matrix out(a.rows_, b.cols_);
        for (std::size_t i = 0; i < a.rows_; ++i) {
            for (std::size_t k = 0; k < a.cols_; ++k) {
                double aik = a(i, k);
                if (aik == 0.0) continue;
                for (std::size_t j = 0; j < b.cols_; ++j) out(i, j) += aik * b(k, j);
            }
        }
        return out;
    }
    Matrix& operator*=(const Matrix& o) { return *this = *this * o; }

    // Integer power by repeated squaring: O(n^3 log e). pow(0) is the identity.
    Matrix pow(unsigned long long e) const {
        if (!isSquare()) throw std::invalid_argument("pow requires a square matrix");
        Matrix result = identity(rows_);
        Matrix base = *this;
        while (e > 0) {
            if (e & 1ULL) result = result * base;
            e >>= 1;
            if (e > 0) base = base * base;
        }
        return result;
    }

    double trace() const {
        if (!isSquare()) throw std::invalid_argument("trace requires a square matrix");
        double t = 0.0;
        for (std::size_t i = 0; i < rows_; ++i) t += (*this)(i, i);
        return t;
    }

    // Determinant by Gaussian elimination with partial pivoting: O(n^3).
    // Each row swap flips the sign; the result is the product of the pivots.
    double determinant() const {
        if (!isSquare()) throw std::invalid_argument("determinant requires a square matrix");
        Matrix m = *this;
        const std::size_t n = rows_;
        double det = 1.0;
        for (std::size_t col = 0; col < n; ++col) {
            std::size_t pivot = col;
            for (std::size_t r = col + 1; r < n; ++r) {
                if (std::fabs(m(r, col)) > std::fabs(m(pivot, col))) pivot = r;
            }
            if (m(pivot, col) == 0.0) return 0.0;
            if (pivot != col) {
                m.swapRows(pivot, col);
                det = -det;
            }
            det *= m(col, col);
            for (std::size_t r = col + 1; r < n; ++r) {
                double f = m(r, col) / m(col, col);
                if (f == 0.0) continue;
                for (std::size_t c = col; c < n; ++c) m(r, c) -= f * m(col, c);
            }
        }
        return det;
    }

    // Rank via row-echelon reduction with partial pivoting. Works for any
    // shape; entries with magnitude below `eps` are treated as zero.
    std::size_t rank(double eps = 1e-10) const {
        Matrix m = *this;
        std::size_t r = 0;
        for (std::size_t col = 0; col < cols_ && r < rows_; ++col) {
            std::size_t pivot = r;
            for (std::size_t i = r + 1; i < rows_; ++i) {
                if (std::fabs(m(i, col)) > std::fabs(m(pivot, col))) pivot = i;
            }
            if (std::fabs(m(pivot, col)) < eps) continue;
            m.swapRows(pivot, r);
            for (std::size_t i = r + 1; i < rows_; ++i) {
                double f = m(i, col) / m(r, col);
                if (f == 0.0) continue;
                for (std::size_t c = col; c < cols_; ++c) m(i, c) -= f * m(r, c);
            }
            ++r;
        }
        return r;
    }

    // Inverse by Gauss-Jordan elimination on [A | I] with partial pivoting.
    // Throws std::domain_error when a pivot is below `eps` (singular or
    // numerically close to singular).
    Matrix inverse(double eps = 1e-12) const {
        if (!isSquare()) throw std::invalid_argument("inverse requires a square matrix");
        const std::size_t n = rows_;
        Matrix a = *this;
        Matrix inv = identity(n);
        for (std::size_t col = 0; col < n; ++col) {
            std::size_t pivot = col;
            for (std::size_t r = col + 1; r < n; ++r) {
                if (std::fabs(a(r, col)) > std::fabs(a(pivot, col))) pivot = r;
            }
            if (std::fabs(a(pivot, col)) < eps) throw std::domain_error("matrix is singular");
            a.swapRows(pivot, col);
            inv.swapRows(pivot, col);

            double p = a(col, col);
            for (std::size_t c = 0; c < n; ++c) {
                a(col, c) /= p;
                inv(col, c) /= p;
            }
            for (std::size_t r = 0; r < n; ++r) {
                if (r == col) continue;
                double f = a(r, col);
                if (f == 0.0) continue;
                for (std::size_t c = 0; c < n; ++c) {
                    a(r, c) -= f * a(col, c);
                    inv(r, c) -= f * inv(col, c);
                }
            }
        }
        return inv;
    }

    // Solves A X = B for X, where B may hold several right-hand-side columns.
    // Gaussian elimination with partial pivoting and back substitution,
    // O(n^3 + n^2 k); cheaper and more accurate than inverse() * B.
    Matrix solve(const Matrix& b, double eps = 1e-12) const {
        if (!isSquare()) throw std::invalid_argument("solve requires a square matrix");
        if (b.rows_ != rows_) throw std::invalid_argument("shape mismatch in solve");
        const std::size_t n = rows_, k = b.cols_;
        Matrix a = *this;
        Matrix x = b;
        for (std::size_t col = 0; col < n; ++col) {
            std::size_t pivot = col;
            for (std::size_t r = col + 1; r < n; ++r) {
                if (std::fabs(a(r, col)) > std::fabs(a(pivot, col))) pivot = r;
            }
            if (std::fabs(a(pivot, col)) < eps) throw std::domain_error("matrix is singular");
            a.swapRows(pivot, col);
            x.swapRows(pivot, col);
            for (std::size_t r = col + 1; r < n; ++r) {
                double f = a(r, col) / a(col, col);
                if (f == 0.0) continue;
                for (std::size_t c = col; c < n; ++c) a(r, c) -= f * a(col, c);
                for (std::size_t c = 0; c < k; ++c) x(r, c) -= f * x(col, c);
            }
        }
        for (std::size_t i = n; i-- > 0;) {
            for (std::size_t c = 0; c < k; ++c) {
                double sum = x(i, c);
                for (std::size_t j = i + 1; j < n; ++j) sum -= a(i, j) * x(j, c);
                x(i, c) = sum / a(i, i);
            }
        }
        return x;
    }

    // Copies row r as a 1 x cols() matrix. Throws std::out_of_range.
    Matrix row(std::size_t r) const { return submatrix(r, 0, 1, cols_); }

    // Copies column c as a rows() x 1 matrix. Throws std::out_of_range.
    Matrix col(std::size_t c) const { return submatrix(0, c, rows_, 1); }

    // Copies the nr x nc block whose top-left corner is (r0, c0).
    // Throws std::out_of_range if the block does not fit inside the matrix.
    Matrix submatrix(std::size_t r0, std::size_t c0, std::size_t nr, std::size_t nc) const {
        if (r0 > rows_ || c0 > cols_ || nr > rows_ - r0 || nc > cols_ - c0) {
            throw std::out_of_range("submatrix block out of range");
        }
        Matrix out(nr, nc);
        for (std::size_t r = 0; r < nr; ++r) {
            for (std::size_t c = 0; c < nc; ++c) out(r, c) = (*this)(r0 + r, c0 + c);
        }
        return out;
    }

    void swapRows(std::size_t a, std::size_t b) {
        check(a, 0);
        check(b, 0);
        if (a == b) return;
        for (std::size_t c = 0; c < cols_; ++c) std::swap((*this)(a, c), (*this)(b, c));
    }

    Matrix transpose() const {
        Matrix t(cols_, rows_);
        for (std::size_t r = 0; r < rows_; ++r) {
            for (std::size_t c = 0; c < cols_; ++c) t(c, r) = (*this)(r, c);
        }
        return t;
    }

    friend bool operator==(const Matrix& a, const Matrix& b) {
        return a.rows_ == b.rows_ && a.cols_ == b.cols_ && a.data_ == b.data_;
    }
    friend bool operator!=(const Matrix& a, const Matrix& b) { return !(a == b); }

    // Element-wise comparison with an absolute tolerance, for floating-point results.
    bool approxEqual(const Matrix& o, double eps = 1e-9) const {
        if (rows_ != o.rows_ || cols_ != o.cols_) return false;
        for (std::size_t i = 0; i < data_.size(); ++i) {
            if (std::fabs(data_[i] - o.data_[i]) > eps) return false;
        }
        return true;
    }

    // Prints one bracketed row per line, e.g. "[1, 2]\n[3, 4]\n".
    friend std::ostream& operator<<(std::ostream& os, const Matrix& m) {
        for (std::size_t r = 0; r < m.rows_; ++r) {
            os << '[';
            for (std::size_t c = 0; c < m.cols_; ++c) {
                if (c) os << ", ";
                os << m(r, c);
            }
            os << "]\n";
        }
        return os;
    }

private:
    std::size_t rows_ = 0;
    std::size_t cols_ = 0;
    std::vector<double> data_;

    void check(std::size_t r, std::size_t c) const {
        if (r >= rows_ || c >= cols_) throw std::out_of_range("matrix index out of range");
    }
    void requireSameShape(const Matrix& o, const char* op) const {
        if (rows_ != o.rows_ || cols_ != o.cols_) {
            throw std::invalid_argument(std::string("shape mismatch in operator") + op);
        }
    }
};

}  // namespace mat
