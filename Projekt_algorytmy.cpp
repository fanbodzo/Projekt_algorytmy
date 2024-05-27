#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

/**
 * @brief Klasa odpowiada za obsluge plikow
 *
 * Klasa przyjmuje nazwe pliku i otwiera go i zapisuje do pliku wynik.txt
 *
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
        ifstream plik(nazwa);
        if (!plik.is_open()) {
            cout << "Nie mozna otworzyc pliku" << endl;
            return;
        }

        string line;
        while (getline(plik, line)) {
            //przeksztalacanie lancucha znakow czyli naszego ciagu na liczby i umieszczenie ich w wektorze
            stringstream ss(line);
            int number;
            while (ss >> number) {
                dane.push_back(number);
            }
        }
        plik.close();
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
    void merge(int* A, int left, int mid, int right) {

        int x = mid - left + 1;
        int y = right - mid;
        //tymczasowe tablice temp
        int* temp_L = new int[x];
        int* temp_R = new int[y];

        // Kopiowanie danych do tablic tymczasowych L[] i R[]
        for (int i = 0; i < x; i++)
            temp_L[i] = A[left + i];
        for (int j = 0; j < y; j++)
            temp_R[j] = A[mid + 1 + j];

        // scalanie tablic temp
        int i = 0; // poczatakowy indeks pierwszej tablicy temp
        int j = 0; // poczatakowy indeks pierwszej tablicy temp
        int k = left; //  pierwszy indeks tablicy do ktorej bedziemy laczyc

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
        // wrzucamy pozostale elementy ktore nie zostaly wrzucone
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
        delete[]  temp_L;
        delete[] temp_R;
    }

    void mergesort(int* tab, int left, int right) {

        if (left < right) {

            int mid = left + (right - left) / 2;
            mergesort(tab, left, mid);
            mergesort(tab, mid + 1, right);
            merge(tab, left, mid, right);
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
        int n = arr.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
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
        vector<int> dane = plik.get_data();
        //bubble.bubblesort(dane);
        //quick.quicksort(dane , 0 , dane.size()-1);
        // do poprawki scalanie zmiana z tablic na vectory
        //scalanie.merge(dane , 0 , (dane.size() - 1)/2, dane.size() - 1);
        kopiec.kopiec_sort(dane);
        plik.set_data(dane);
        plik.wyswietl_dane();
        plik.zapisz_do_pliku(dane);
        
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