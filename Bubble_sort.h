#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

#include <vector>
#include <chrono>

/**
* @brief Klasa odpowiadajaca za sortowanie babelkowe
*
* Klasa przyjmuje vektor i zwraca go w kolejnosci od najmnijeszej liczby do najwiekszej
*
* @param ciag - vektory ktory jest ciagiem liczb
* @return posortowany ciag liczb w kolejnosci od najmnijeszej do najwiekszej
*/
class Bubble_sort {
public:
    void bubblesort(std::vector<int>& arr);
    void swap(int& a, int& b);
};

#endif