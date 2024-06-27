#include "dane.h"
#include <fstream>
#include <sstream>
#include <iostream>

void DaneImpl::Wczytanie_Danych(const std::string& plik) {
    std::ifstream file(plik);
    if (!file.is_open()) {
        std::cerr << "Nie można otworzyć pliku: " << plik << "\n";
        return;
    }

    std::string line;
    liczba_wierszy = 0;
    liczba_kolumn = 0;

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string token;
        std::vector<std::string> row;
        while (std::getline(ss, token, ',')) {
            row.push_back(token);
        }

        if (liczba_kolumn == 0) {
            liczba_kolumn = row.size();
        }

        dane.push_back(row);
        liczba_wierszy++;
    }

    file.close();
}

void DaneImpl::Zapisanie_Danych(const std::string& plik) {
    std::ofstream file(plik);
    if (!file.is_open()) {
        std::cerr << "Nie można otworzyć pliku do zapisu: " << plik << "\n";
        return;
    }

    for (const auto& row : dane) {
        for (size_t i = 0; i < row.size(); ++i) {
            file << row[i];
            if (i < row.size() - 1) {
                file << ",";
            }
        }
        file << "\n";
    }

    file.close();
}

void DaneImpl::Wyswietlanie_Procesu(int obecny, int calkowity) {
    int procent = (obecny * 100) / calkowity;
    std::cout << "\rPostęp: " << procent << "%";
}
