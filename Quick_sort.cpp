#include "Quick_sort.h"
#include <chrono>
#include <iostream>

void Quick_sort::quicksort_czas(std::vector<int>& arr) {
    auto start = std::chrono::steady_clock::now();
    quicksort(arr, 0, arr.size() - 1);
    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    std::cout << "Czas sortowania: " << std::chrono::duration<double, std::milli>(diff).count() << " ms" << std::endl;
}

void Quick_sort::quicksort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

int Quick_sort::partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void Quick_sort::swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}