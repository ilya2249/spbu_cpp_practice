#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <set>
#include <vector>

#include "my_sort.h"
#include "point.h"

void testInts(std::vector<int> values) {
    std::multiset<int> original(values.begin(), values.end());
    mySort(values.begin(), values.end());
    assert(original == std::multiset<int>(values.begin(), values.end()));
}

void testPoints(std::vector<Point> values) {
    auto original = values;
    mySort(values.begin(), values.end(), comparePoints);
    assert(std::is_sorted(values.begin(), values.end(), comparePoints));
    assert(values.size() == original.size());
}

int main() {
    testInts({});                              // Empty
    testInts({42});                            // One element
    testInts({1, 2, 3, 4, 5});                  // Sorted
    testInts({5, 4, 3, 2, 1});                  // Reversed
    testInts({7, 7, 7, 7, 7});                  // All equal
    testInts({-5, -1, -10, -3, -2});            // Negative
    testInts({3, 1, 3, 2, 1, 2});               // Duplicates

    testPoints({});                            // Empty
    testPoints({{3, 4}});                      // One element
    testPoints({{0, 0}, {1, 0}, {0, 2}, {3, 4}}); // Sorted
    testPoints({{3, 4}, {0, 2}, {1, 0}, {0, 0}}); // Reversed
    testPoints({{1, 2}, {1, 2}, {1, 2}});       // All equal
    testPoints({{3, 4}, {0, 0}, {3, 4}, {0, 0}}); // Duplicates
    testPoints({{3, 4}, {-3, 4}, {0, 5}, {5, 0}}); // Equal distances

    std::mt19937 generator(12345);
    std::uniform_int_distribution<int> distribution(-10000, 10000);

    for (int size : {10, 1000, 100000}) {
        std::vector<int> numbers(size);
        std::vector<Point> points(size);

        for (int i = 0; i < size; ++i) {
            numbers[i] = distribution(generator);
            points[i] = {static_cast<double>(distribution(generator)),
                         static_cast<double>(distribution(generator))};
        }

        testInts(numbers);
        testPoints(points);
    }

    std::cout << "All tests passed!\n";
}
