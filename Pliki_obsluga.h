#ifndef PLIKI_OBSLUGA_H
#define PLIKI_OBSLUGA_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

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
    std::string nazwa;
    std::vector<int> dane;

public:
    Pliki_obsluga(const std::string& file_name);
    void read_file();
    void zapisz_do_pliku(const std::vector<int>& sorted_data);
    void wyswietl_dane();
    std::vector<int> get_data() const;
    void set_data(const std::vector<int>& new_data);
};

#endif