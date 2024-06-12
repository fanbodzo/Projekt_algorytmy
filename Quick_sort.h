#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include <vector>
#include <chrono>

class Quick_sort {
public:
    void quicksort_czas(std::vector<int>& arr);
    void quicksort(std::vector<int>& arr, int low, int high);
    int partition(std::vector<int>& arr, int low, int high);
    void swap(int& a, int& b);
};

#endif
