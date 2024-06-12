#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

#include <vector>
#include <chrono>

class Bubble_sort {
public:
    void bubblesort(std::vector<int>& arr);
    void swap(int& a, int& b);
};

#endif