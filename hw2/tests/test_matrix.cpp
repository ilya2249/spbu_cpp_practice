#include <cmath>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>

#include "dense_matrix.h"

namespace {
constexpr double tolerance = 1e-9;
using Multiply = DenseMatrix (DenseMatrix::*)(const DenseMatrix&) const;

void require(bool condition, const std::string& message) {
    // Unlike assert, these checks also run with NDEBUG (Release).
    if (!condition) throw std::runtime_error(message);
}

void checkEqual(const DenseMatrix& actual, const DenseMatrix& expected) {
    require(actual.rows() == expected.rows() && actual.cols() == expected.cols(),
            "Wrong result dimensions");
    for (std::size_t i = 0; i < actual.rows(); ++i) {
        for (std::size_t j = 0; j < actual.cols(); ++j) {
            require(std::isfinite(actual.at(i, j)) &&
                    std::abs(actual.at(i, j) - expected.at(i, j)) <= tolerance,
                    "Wrong result at (" + std::to_string(i) + ", " +
                    std::to_string(j) + ")");
        }
    }
}

DenseMatrix identity(std::size_t size) {
    DenseMatrix result(size, size);
    for (std::size_t i = 0; i < size; ++i) result.at(i, i) = 1.0;
    return result;
}

void testImplementation(Multiply multiply) {
    DenseMatrix a(2, 3);
    a.at(0, 0) = 1; a.at(0, 1) = -2; a.at(0, 2) = 3;
    a.at(1, 0) = 4; a.at(1, 1) = 0; a.at(1, 2) = -1;
    checkEqual((a.*multiply)(identity(3)), a);
    checkEqual((identity(2).*multiply)(a), a);
    checkEqual((a.*multiply)(DenseMatrix(3, 4)), DenseMatrix(2, 4));
    checkEqual((DenseMatrix(4, 2).*multiply)(a), DenseMatrix(4, 3));

    DenseMatrix b(3, 2);
    b.at(0, 0) = 2; b.at(0, 1) = 1;
    b.at(1, 0) = 3; b.at(1, 1) = -2;
    b.at(2, 0) = -1; b.at(2, 1) = 4;
    DenseMatrix expected(2, 2);
    // [1*2-2*3+3*(-1), 1*1+(-2)*(-2)+3*4] = [-7, 17]
    // [4*2+0*3+(-1)*(-1), 4*1+0*(-2)+(-1)*4] = [9, 0]
    expected.at(0, 0) = -7; expected.at(0, 1) = 17;
    expected.at(1, 0) = 9; expected.at(1, 1) = 0;
    checkEqual((a.*multiply)(b), expected);

    bool threw = false;
    try {
        (a.*multiply)(DenseMatrix(4, 2));
    } catch (const std::invalid_argument&) {
        threw = true;
    }
    require(threw, "Incompatible dimensions must throw std::invalid_argument");

    checkEqual((DenseMatrix(2, 0).*multiply)(DenseMatrix(0, 3)), DenseMatrix(2, 3));
    checkEqual((DenseMatrix(0, 2).*multiply)(a), DenseMatrix(0, 3));
    checkEqual((a.*multiply)(DenseMatrix(3, 0)), DenseMatrix(2, 0));
}

void testRandom() {
    std::mt19937 generator(12345);
    std::uniform_real_distribution<double> distribution(-10.0, 10.0);
    const std::size_t shapes[][3] = {
        {1, 1, 1}, {2, 2, 2}, {2, 3, 4}, {7, 1, 9},
        {1, 13, 1}, {13, 7, 19}, {32, 32, 32}, {64, 64, 64}
    };
    for (const auto& shape : shapes) {
        for (int repeat = 0; repeat < 3; ++repeat) {
            DenseMatrix a(shape[0], shape[1]), b(shape[1], shape[2]);
            for (std::size_t i = 0; i < a.rows(); ++i)
                for (std::size_t j = 0; j < a.cols(); ++j)
                    a.at(i, j) = distribution(generator);
            for (std::size_t i = 0; i < b.rows(); ++i)
                for (std::size_t j = 0; j < b.cols(); ++j)
                    b.at(i, j) = distribution(generator);
            checkEqual(a.OptimizedMultiply(b), a.multiplyNaive(b));
        }
    }
}
} // namespace

int main() {
    try {
        testImplementation(&DenseMatrix::multiplyNaive);
        testImplementation(&DenseMatrix::OptimizedMultiply);
        testRandom();
        std::cout << "All matrix tests passed (absolute tolerance 1e-9).\n";
    } catch (const std::exception& error) {
        std::cerr << "Matrix test failed: " << error.what() << '\n';
        return 1;
    }
}
