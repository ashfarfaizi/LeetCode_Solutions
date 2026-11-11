// matrix-lib: a small header-only dense matrix of doubles.
#pragma once

#include <cmath>
#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <string>
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
