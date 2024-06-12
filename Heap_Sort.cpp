#include "Heap_sort.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

void Heap_sort::wlasnosc_kopca(std::vector<int>& dane, int n, int i) {
    int korzen = i; // najwiekszy element jako korzen
    int left = 2 * i + 1; // lewe dziecko
    int right = 2 * i + 2; // prawe dziecko

    // czy lewe dziecko istnieje i czy jest wieksze od korzenia
    if (left < n && dane[left] > dane[korzen])
        korzen = left;

    // czy prawe dziecko istnieje i czy jest wieksze od korzenia lub lewego dziecka
    if (right < n && dane[right] > dane[korzen])
        korzen = right;

    // gdy najwiekszy element nie jest korzeniem
    if (korzen != i) {
        swap(dane[i], dane[korzen]);

        // rekurencyjnie przywracanie wlasnosci kopca
        wlasnosc_kopca(dane, n, korzen);
    }
}

void Heap_sort::kopiec_sort(std::vector<int>& dane) {
        auto start = chrono::steady_clock::now();

        int n = dane.size();

        // budowanie kopca
        for (int i = n / 2 - 1; i >= 0; i--)
            wlasnosc_kopca(dane, n, i);

        for (int i = n - 1; i > 0; i--) {
            // zamiana korzenia z ostatnim elementem
            swap(dane[0], dane[i]);

            // zmniejszenie kopca i przywracanie wlasnosci kopca
            wlasnosc_kopca(dane, i, 0);
        }
        auto end = chrono::steady_clock::now();
        auto diff = end - start;
        cout << "Czas sortowania: " << chrono::duration <double, milli>(diff).count() << " ms" << endl;
    
}