#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <vector>
#include <chrono>

class Merge_sort {
public:
    void merge_czas(std::vector<int>& dane);
    void merge(std::vector<int>& A, int left, int mid, int right);
    void mergesort(std::vector<int>& A, int left, int right);
};

#endif
