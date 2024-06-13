#ifndef HEAP_SORT_H
#define HEAP_SORT_H

#include <vector>
#include <chrono>

/**
 * @brief Klasa odpowiadajaca za sortowanie przez kopcowanie
 *
 * Klasa przyjmuje vektor i zwraca go w kolejnosci od najmnijeszej liczby do najwiekszej
 *
 * @param ciag - vektory ktory jest ciagiem liczb
 * @return posortowany ciag liczb w kolejnosci od najmnijeszej do najwiekszej
 */

class Heap_sort {
public:
    void wlasnosc_kopca(std::vector<int>& dane, int n, int i);
    void kopiec_sort(std::vector<int>& dane);
};

#endif
