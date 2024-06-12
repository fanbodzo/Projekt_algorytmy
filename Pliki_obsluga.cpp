#include "Pliki_obsluga.h"


Pliki_obsluga::Pliki_obsluga(const std::string& file_name) : nazwa(file_name) {}

void Pliki_obsluga::read_file() {
    do {
        std::ifstream plik(nazwa);
        if (!plik.is_open()) {
            std::cout << "Nie mozna otworzyc pliku" << std::endl;
            std::cout << "Wprowadz poprawna nazwe pliku: ";
            std::cin >> nazwa;
            nazwa += ".txt";
        }
        else {
            std::string line;
            while (std::getline(plik, line)) {
                std::stringstream ss(line);
                int number;
                while (ss >> number) {
                    dane.push_back(number);
                }
            }
            plik.close();
        }
    } while (dane.empty());
}

void Pliki_obsluga::zapisz_do_pliku(const std::vector<int>& sorted_data) {
    std::ofstream wynik("wynik.txt");
    if (wynik.is_open()) {
        for (int num : sorted_data) {
            wynik << num << " ";
        }
        wynik.close();
        std::cout << "Dane zostaly zapisane do pliku wynik.txt" << std::endl;
    }
    else {
        std::cout << "Nie mozna otworzyc pliku wynik.txt" << std::endl;
    }
}

void Pliki_obsluga::wyswietl_dane() {
    std::cout << "Liczby: " << std::endl;
    for (int num : dane) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

std::vector<int> Pliki_obsluga::get_data() const {
    return dane; // Zwracanie danych
}

void Pliki_obsluga::set_data(const std::vector<int>& new_data) {
    dane = new_data;
}