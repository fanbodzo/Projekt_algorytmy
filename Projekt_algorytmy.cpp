#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iostream>
#include "Pliki_obsluga.h"
#include "Bubble_sort.h"
#include "Quick_sort.h"
#include "Merge_sort.h"
#include "Heap_sort.h"
using namespace std;


/**
 * @brief Klasa odpowiadajaca za obsluge uzytkownika
 *
 * Klasa przyjmuje dane od uzytkownika oraz wyswietla wyniki
 *
 * @param ciag - ciag znakow wskazujacy na sciezke pliku
 * @return zwraca informacje do uzytkownika 
 */
class Algorytmy {
private:
    //tworzymy obiekty klas
    Pliki_obsluga plik;
    Bubble_sort bubble;
    Quick_sort quick;
    Merge_sort scalanie;
    Heap_sort kopiec;
public:
    //konstruktor
    Algorytmy(const string& file_name) : plik(file_name) {
        //odrazu odowlujemy sie zeby nam przeczytalo plik i wyswietlio pomocniczo ciag
        plik.read_file();
        plik.wyswietl_dane();
        // zabezpieczyc plik ze jak uzytkownik wprowadzi zla nazwe pliku to wtedy kaze mu wprowadzic nazwe jeszcze raz
        menu();
        
    }
    // metoda odpowiadajaca za menu w ktorym uzytkownik  moze wybierac algorytm do uzycia
    void menu() {
        int wybor;
        bool test = false;
        cout << "Wybierz algorytm ktory chcesz uzyc do sortowania swoich liczb poprzez wprowadznie z klawiatury liczby ktora stoi obok algorytmu" << endl;
        cout << "1. Sortowanie babelkowe" << endl;
        cout << "2. Sortowanie Szybkie" << endl;
        cout << "3. Sortowanie przez Scalanie" << endl;
        cout << "4. Sortowanie przez Kopcowanie" << endl;

        vector<int> dane = plik.get_data();
        //petla while zabezpieczajaca zeby uzytkownik nie wybral liczby innej niz z zakresu 1 - 4
        do {
            cin >> wybor;
            //switch odpowiadajcy za wybor algorytmu przez uzytkownika
            switch (wybor) {
            case 1:
                bubble.bubblesort(dane);
                plik.set_data(dane);
                plik.wyswietl_dane();
                plik.zapisz_do_pliku(dane);
                test = true;
                return;

            case 2:
                quick.quicksort_czas(dane); //, 0, dane.size() - 1);
                plik.set_data(dane);
                plik.wyswietl_dane();
                plik.zapisz_do_pliku(dane);
                test = true;
                return;

            case 3:
                scalanie.merge_czas(dane); // , 0, ((dane.size()) / 2) - 1, dane.size() - 1);
                plik.set_data(dane);
                plik.wyswietl_dane();
                plik.zapisz_do_pliku(dane);
                test = true;
                return;

            case 4:
                kopiec.kopiec_sort(dane);
                plik.set_data(dane);
                plik.wyswietl_dane();
                plik.zapisz_do_pliku(dane);
                test = true;
                return;

            default:
                cout << "Wybrana liczba nie odpowiada zadnemu algorytmowi wybierz liczbe z zakresu 1 - 4" << endl;
                test = false;
            }
        } while (!test);


    }

};

int main()
{
    string file_name;

    cout << "Wprowadz nazwe pliku z ciagiem liczb, ktory chcesz posortowac." << endl;
    cin >> file_name;

    // unikamy w ten sposob niepotrzebnego wprowdzania .txt po nazwie pliku
    file_name += ".txt";
    Algorytmy sortowanie(file_name);
   
    return 0;
   
}