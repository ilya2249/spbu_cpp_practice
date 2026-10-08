#include <iostream>
#include "my_sort.h"
int main() {

   vector<int>arr = {5, 2, 9, 1, 5, 6};
    vector<int>result = merge_sort(arr);
    for (int i = 0; i < result.size(); i++){
        cout << result[i] << " ";
    }
    return 0;
}
