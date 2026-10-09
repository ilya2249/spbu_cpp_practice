#include <iostream>
#include "my_sort.h"
#include "point.h"
int main() {

    vector<Point>arr = {{5, 2}, {9, 1}, {5, 6}};
    vector<Point>result = merge_sort(arr, comparePoints);
    for (const auto& p : result) {
        cout << "(" << p.x << ", " << p.y << ") ";
    }
    return 0;
}
