#include "Bubble_sort.h"
#include <ctime>
#include <algorithm>
#include <iostream>

using namespace std;

void Bubble_sort::bubblesort(std::vector<int>& arr) {
    auto start = chrono::steady_clock::now();
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    cout << "Czas sortowania: " << chrono::duration <double, milli>(diff).count() << " ms" << endl;
}

void Bubble_sort::swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}