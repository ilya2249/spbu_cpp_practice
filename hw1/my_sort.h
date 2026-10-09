#pragma once
#include <vector>
#include <functional>
#include <iterator>
using namespace std;
template <typename T, typename Compare>
vector<T> merge(const vector<T>&left, const vector<T>&right, Compare comp){
    vector<T>result;
    size_t i = 0;
    size_t j = 0;  
    while(i < left.size() && j < right.size()){
        if (comp(left[i], right[j])){
            result.push_back(left[i]);
            i++;
        }
        else{
            result.push_back(right[j]);
            j++;
        }
    }
    while(i < left.size()){
        result.push_back(left[i]);
        i++;
    }
    while(j < right.size()){
        result.push_back(right[j]);
        j++;
    }
    return result;
}
template <typename T, typename Compare = std::less<T>>
vector<T>merge_sort(const vector<T>&arr, Compare comp = Compare{}){
    if (arr.size()<=1) {
        return arr;
    }
    size_t mid = arr.size()/2;
    vector<T>left;
    for (size_t i = 0; i< mid; i++){
        left.push_back(arr[i]);
    }
    vector<T>right;
    for (size_t i = mid; i< arr.size(); i++){
        right.push_back(arr[i]);
    }
    
    return merge(merge_sort(left, comp),merge_sort(right, comp),comp);

}
template <typename It, typename Compare = less<typename iterator_traits<It>::value_type>>
void mySort(It first, It last, Compare comp = Compare{}){
    using T = typename std::iterator_traits<It>::value_type;
    vector<T>arr(first, last);
    vector<T>result = merge_sort(arr, comp);
    auto it = first;
    for (const auto& elem : result) {
        *it = elem; 
        ++it;
    }
}