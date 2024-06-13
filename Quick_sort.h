#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include <vector>
#include <chrono>

/**
 * @brief Klasa odpowiadajaca za sortowanie szybkie
 *
 * Klasa przyjmuje vektor i zwraca go w kolejnosci od najmnijeszej liczby do najwiekszej
 *
 * @param ciag - vektory ktory jest ciagiem liczb
 * @return posortowany ciag liczb w kolejnosci od najmnijeszej do najwiekszej
 */

class Quick_sort {
public:
    void quicksort_czas(std::vector<int>& arr);
    void quicksort(std::vector<int>& arr, int low, int high);
    int partition(std::vector<int>& arr, int low, int high);
    void swap(int& a, int& b);
};

#endif
