#ifndef HEAP_SORT_H
#define HEAP_SORT_H

#include <vector>
#include <chrono>


class Heap_sort {
public:
    void wlasnosc_kopca(std::vector<int>& dane, int n, int i);
    void kopiec_sort(std::vector<int>& dane);
};

#endif
