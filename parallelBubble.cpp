#include <iostream>
#include <vector>
#include <omp.h>
#include<bits/stdc++.h>
using namespace std;

vector<int> bubble_sort_parallel(vector<int>& arr) {
    int size = arr.size();

    #pragma omp parallel
    {
        for (int i = 0; i < size; i++) {
            #pragma omp parallel for
            for (int j = 0; j < size - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    }

    return arr;
}

int main() {
    vector<int> arr = {9, 5, 1, 8, 3, 10, 2, 7, 6, 4};

    vector<int> sorted_arr = bubble_sort_parallel(arr);
    cout<<"sorted array is " << endl;
    for (int num : sorted_arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}