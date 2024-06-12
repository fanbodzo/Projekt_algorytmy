#include "Merge_sort.h"
#include <iostream>
#include <algorithm>
#include <ctime>
#include <vector>

using namespace std;

void Merge_sort::merge_czas(std::vector<int>& dane) {
    auto start = chrono::steady_clock::now();

    mergesort(dane, 0, dane.size() - 1);

    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    cout << "Czas sortowania: " << chrono::duration <double, milli>(diff).count() << " ms" << endl;
}

void Merge_sort::merge(std::vector<int>& A, int left, int mid, int right) {

    int x = mid - left + 1;
    int y = right - mid;

    // tymczasowe wektory temp
    vector<int> temp_L(x);
    vector<int> temp_R(y);

    // Kopiowanie danych do wektor�w tymczasowych L[] i R[]
    for (int i = 0; i < x; i++)
        temp_L[i] = A[left + i];
    for (int j = 0; j < y; j++)
        temp_R[j] = A[mid + 1 + j];

    // scalanie wektor�w temp
    int i = 0; // poczatakowy indeks pierwszego wektora temp
    int j = 0; // poczatakowy indeks drugiego wektora temp
    int k = left; // pierwszy indeks wektora do kt�rego b�dziemy �aczy�

    while (i < x && j < y) {
        if (temp_L[i] <= temp_R[j]) {
            A[k] = temp_L[i];
            i++;
        }
        else {
            A[k] = temp_R[j];
            j++;
        }
        k++;
    }
    // wrzucamy pozosta�e elementy kt�re nie zosta�y wrzucone
    while (i < x) {
        A[k] = temp_L[i];
        i++;
        k++;
    }
    while (j < y) {
        A[k] = temp_R[j];
        j++;
        k++;
    }

}

void Merge_sort::mergesort(std::vector<int>& A, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergesort(A, left, mid);
        mergesort(A, mid + 1, right);
        merge(A, left, mid, right);
    }
}