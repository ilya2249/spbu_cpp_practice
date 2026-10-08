#pragma once
#include <vector>
using namespace std;

inline vector<int> merge(const vector<int>&left, const vector<int>&right){
    vector<int>result;
    size_t i = 0;
    size_t j = 0;  
    while(i < left.size() && j < right.size()){
        if (left[i] <= right[j]){
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
inline vector<int>merge_sort(const vector<int>&arr){
    if (arr.size()<=1) {
        return arr;
    }
    size_t mid = arr.size()/2;
    vector<int>left;
    for (size_t i = 0; i< mid; i++){
        left.push_back(arr[i]);
    }
    vector<int>right;
    for (size_t i = mid; i< arr.size(); i++){
        right.push_back(arr[i]);
    }
    return merge(merge_sort(left), merge_sort(right));
    

}