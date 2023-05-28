#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

void merge(vector<int>& arr, int left, int mid, int right) {
int n1 = mid - left + 1;
int n2 = right - mid;

    vector<int> L(n1);
    vector<int> R(n2);

for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }

for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

int i = 0, j = 0, k = left;
while (i < n1 && j < n2) {
if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort(vector<int>& arr, int left, int right) {
if (left < right) {
int mid = left + (right - left) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                merge_sort(arr, left, mid);
            }
            #pragma omp section
            {
                merge_sort(arr, mid + 1, right);
            }
        }

        merge(arr, left, mid, right);
    }
}

int main() {
    vector<int> arr = {9, 5, 1, 8, 3, 10, 2, 7, 6, 4};
int size = arr.size();

    cout << "Unsorted array:" << endl;
for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    merge_sort(arr, 0, size - 1);

    cout << "Sorted array:" << endl;
for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;