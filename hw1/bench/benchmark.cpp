#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <functional>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

#include "my_sort.h"
#include "point.h"

void printHeader(const char* title) {
    std::cout << '\n' << title << '\n'
              << std::setw(12) << "Size"
              << std::setw(16) << "mySort (ms)"
              << std::setw(18) << "std::sort (ms)"
              << std::setw(20) << "mySort / std::sort" << '\n';
}

template <typename T, typename Compare>
void benchmark(const std::vector<T>& data, Compare comp) {
    double myTime = 0;
    double stdTime = 0;
    const int repeats = 3;

    for (int i = 0; i < repeats; ++i) {
        auto myData = data;
        auto stdData = data;

        auto start = std::chrono::steady_clock::now();
        mySort(myData.begin(), myData.end(), comp);
        auto finish = std::chrono::steady_clock::now();
        myTime += std::chrono::duration<double, std::milli>(finish - start).count();

        start = std::chrono::steady_clock::now();
        std::sort(stdData.begin(), stdData.end(), comp);
        finish = std::chrono::steady_clock::now();
        stdTime += std::chrono::duration<double, std::milli>(finish - start).count();

        // Check the result outside the timed section, including in Release.
        if (!std::is_sorted(myData.begin(), myData.end(), comp) ||
            !std::is_sorted(stdData.begin(), stdData.end(), comp)) {
            std::cerr << "Sorting failed!\n";
            std::exit(1);
        }
    }

    myTime /= repeats;
    stdTime /= repeats;
    std::cout << std::setw(12) << data.size()
              << std::setw(16) << myTime
              << std::setw(18) << stdTime;
    if (stdTime > 0) {
        std::cout << std::setw(20) << myTime / stdTime << '\n';
    } else {
        std::cout << std::setw(20) << "N/A" << '\n';
    }
}

int main() {
    std::mt19937 generator(12345);
    std::uniform_int_distribution<int> distribution(-1000000, 1000000);
    std::cout << std::fixed << std::setprecision(3);
    std::cout << "Average of 3 runs; times in milliseconds.\n";

    printHeader("int: random data");
    std::vector<int> numbers;
    for (int size : {1000, 10000, 100000, 1000000}) {
        numbers.resize(size);
        for (auto& number : numbers) {
            number = distribution(generator);
        }
        benchmark(numbers, std::less<int>{});
    }

    numbers.resize(100000);
    std::sort(numbers.begin(), numbers.end());
    printHeader("int: already sorted data");
    benchmark(numbers, std::less<int>{});

    printHeader("Point: random data");
    std::vector<Point> points;
    for (int size : {1000, 10000, 100000, 1000000}) {
        points.resize(size);
        for (auto& point : points) {
            point = {static_cast<double>(distribution(generator)),
                     static_cast<double>(distribution(generator))};
        }
        benchmark(points, comparePoints);
    }

    points.resize(100000);
    std::sort(points.begin(), points.end(), comparePoints);
    printHeader("Point: already sorted data");
    benchmark(points, comparePoints);
}
