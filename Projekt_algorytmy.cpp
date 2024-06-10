#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;

/**
 * @brief Klasa odpowiada za obsluge plikow
 *
 * Klasa przyjmuje nazwe pliku i otwiera go i zapisuje do pliku wynik.txt
 * :)
 * @param file_name - nazwa pliku ktory otiweramy
 * @return Zwraca otworzony plik jako vektor
 */
class Pliki_obsluga {
private:
    string nazwa;
    vector<int> dane;

public:
    // deklaracja przyjacielskiej klasy zeby miec mozliwosc uzywania prywatnej zmiennej
    friend class Algorytmy;
    //konstruktor 
    Pliki_obsluga(const string& file_name) : nazwa(file_name){}

    void read_file() {
        do {
            ifstream plik(nazwa);
            if (!plik.is_open()) {
                cout << "Nie mozna otworzyc pliku" << endl;
                cout << "Wprowadz poprawna nazwe pliku: ";
                cin >> nazwa;
                nazwa += ".txt";
            }
            else {
                string line;
                while (getline(plik, line)) {
                    stringstream ss(line);
                    int number;
                    while (ss >> number) {
                        dane.push_back(number);
                    }
                }
                plik.close();
            }
        } while (dane.empty()); 
    }

    void zapisz_do_pliku(const vector<int>& sorted_data) {
        ofstream wynik("wynik.txt");
        if (wynik.is_open()) {
            for (int num : sorted_data) {
                wynik << num << " ";
            }
            wynik.close();
            cout << "Dane zostaly zapisane do pliku wynik.txt" << endl;
        }
        else {
            cout << "Nie mozna otworzyc pliku wynik.txt" << endl;
        }
    }

    void wyswietl_dane() {
        cout << "Liczby: " << endl;
        for (int num : dane) {
            cout << num << " ";
        }
        cout << endl;
    }

    vector<int> get_data() const {  //umozliwiam klasom dostep do kopii danych, sluzy to bezpieczenstwu zeby oryginalne dane nie zostaly naruszone
        return dane;
    }
    //potrzebna metoda zeby ustawic nowa wartosc dla wektora danych po sortowaniu juz
    void set_data(const vector<int>& new_data) {
        dane = new_data;
    }

};

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
    void wlasnosc_kopca(vector<int>& dane, int n, int i) {
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

    // sortowanie przez kopcowanie
    void kopiec_sort(vector<int>& dane) {
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

};

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

    void merge_czas(vector<int>& dane) {
        auto start = chrono::steady_clock::now();

        mergesort(dane, 0, dane.size() - 1);

        auto end = chrono::steady_clock::now();
        auto diff = end - start;
        cout << "Czas sortowania: " << chrono::duration <double, milli>(diff).count() << " ms" << endl;
    }

    void merge(vector<int>& A, int left, int mid, int right) {

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
            } else {
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

    void mergesort(vector<int>& A, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergesort(A, left, mid);
            mergesort(A, mid + 1, right);
            merge(A, left, mid, right);
        }
      
    }
    
};

/**
 * @brief Klasa odpowiadajaca za sortowanie babelkowe
 *
 * Klasa przyjmuje vektor i zwraca go w kolejnosci od najmnijeszej liczby do najwiekszej
 *
 * @param ciag - vektory ktory jest ciagiem liczb
 * @return posortowany ciag liczb w kolejnosci od najmnijeszej do najwiekszej
 */
class Bubble_sort { //1sza wersja bubble sort do przetestowania
public:
    void bubblesort(vector<int>& arr) {
        auto start = chrono::steady_clock::now();
        int n = arr.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
        auto end = chrono::steady_clock::now(); 
        auto diff = end - start;
        cout << "Czas sortowania: " << chrono::duration <double, milli>(diff).count() << " ms" << endl;
    }

    void swap(int& a, int& b) {
        int temp = a;
        a = b;
        b = temp;
    }
};


/**
 * @brief Klasa odpowiadajaca za sortowanie szybkie
 *
 * Klasa przyjmuje vektor i zwraca go w kolejnosci od najmnijeszej liczby do najwiekszej
 *
 * @param ciag - vektory ktory jest ciagiem liczb
 * @return posortowany ciag liczb w kolejnosci od najmnijeszej do najwiekszej
 */
class Quick_sort {//1sza wersja do przetestowania
public:
    void quicksort_czas(vector<int>& arr) {
        auto start = chrono::steady_clock::now();
        quicksort(arr, 0, arr.size() - 1);
        auto end = chrono::steady_clock::now();
        auto diff = end - start;
        cout << "Czas sortowania: " << chrono::duration <double, milli>(diff).count() << " ms" << endl;
    }

    void quicksort(vector<int>& arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            quicksort(arr, low, pi - 1);
            quicksort(arr, pi + 1, high);

        }
    }

    int partition(vector<int>& arr, int low, int high) {
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return i + 1;
    }

    void swap(int& a, int& b) {
        int temp = a;
        a = b;
        b = temp;
    }

};

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