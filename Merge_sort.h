#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <vector>
#include <chrono>

/**
 * @brief Klasa odpowiadajaca za sortowanie przez scalanie
 *
 * Klasa przyjmuje vektor i zwraca go w kolejnosci od najmnijeszej liczby do najwiekszej
 *
 * @param ciag - vektory ktory jest ciagiem liczb
 * @return posortowany ciag liczb w kolejnosci od najmnijeszej do najwiekszej
 */
class Merge_sort {
public:
    void merge_czas(std::vector<int>& dane);
    void merge(std::vector<int>& A, int left, int mid, int right);
    void mergesort(std::vector<int>& A, int left, int right);
};

#endif
