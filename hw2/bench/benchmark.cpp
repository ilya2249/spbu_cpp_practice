#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>

#include "dense_matrix.h"

namespace {
using Clock = std::chrono::steady_clock;
constexpr int repeats = 3;
constexpr double tolerance = 1e-9;

void benchmark(std::size_t size, std::mt19937& generator) {
    std::uniform_real_distribution<double> distribution(-1.0, 1.0);
    DenseMatrix a(size, size), b(size, size);
    for (std::size_t i = 0; i < size; ++i) {
        for (std::size_t j = 0; j < size; ++j) {
            a.at(i, j) = distribution(generator);
            b.at(i, j) = distribution(generator);
        }
    }

    double naiveTime = 0, optimizedTime = 0, checksum = 0;
    for (int repeat = 0; repeat < repeats; ++repeat) {
        DenseMatrix naive(0, 0), optimized(0, 0);
        const auto runNaive = [&] {
            const auto start = Clock::now();
            naive = a.multiplyNaive(b);
            naiveTime += std::chrono::duration<double, std::milli>(Clock::now() - start).count();
        };
        const auto runOptimized = [&] {
            const auto start = Clock::now();
            optimized = a.OptimizedMultiply(b);
            optimizedTime += std::chrono::duration<double, std::milli>(Clock::now() - start).count();
        };
        // Alternate order to reduce systematic bias from always running first.
        if (repeat % 2 == 0) { runNaive(); runOptimized(); }
        else { runOptimized(); runNaive(); }

        // Read every result outside the timer, also preventing dead-code removal.
        for (std::size_t i = 0; i < size; ++i) {
            for (std::size_t j = 0; j < size; ++j) {
                const double x = naive.at(i, j), y = optimized.at(i, j);
                if (!std::isfinite(x) || !std::isfinite(y) || std::abs(x - y) > tolerance)
                    throw std::runtime_error("Multiplication results differ");
                checksum += x + y;
            }
        }
    }
    naiveTime /= repeats;
    optimizedTime /= repeats;
    std::cout << std::setw(8) << size
              << std::setw(16) << naiveTime
              << std::setw(18) << optimizedTime;
    if (optimizedTime > 0) std::cout << std::setw(14) << naiveTime / optimizedTime;
    else std::cout << std::setw(14) << "N/A";
    std::cout << std::setw(18) << checksum << std::endl;
}
} // namespace

int main() {
    if (std::string(HW2_BUILD_CONFIG) != "Release") {
        std::cerr << "Benchmark requires Release. Build with cmake --preset release\n";
        return 1;
    }
    try {
        std::cout << "Configuration: " << HW2_BUILD_CONFIG
                  << "; compiler: " << HW2_COMPILER
                  << "; optimization: " << HW2_OPTIMIZATION << '\n'
                  << "Average of " << repeats << " runs; times in milliseconds.\n"
                  << "Speedup = naive / optimized; seed = 12345; tolerance = 1e-9.\n"
                  << std::fixed << std::setprecision(3)
                  << std::setw(8) << "Size"
                  << std::setw(16) << "Naive (ms)"
                  << std::setw(18) << "Optimized (ms)"
                  << std::setw(14) << "Speedup"
                  << std::setw(18) << "Checksum" << std::endl;
        std::mt19937 generator(12345);
        for (std::size_t size : {100, 200, 500, 1000}) benchmark(size, generator);
    } catch (const std::exception& error) {
        std::cerr << "Benchmark failed: " << error.what() << '\n';
        return 1;
    }
}
