#include "diagnoza.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <sstream>

bool isNumber(const std::string& s) {
    try {
        std::stod(s);
    }
    catch (const std::invalid_argument& e) {
        return false;
    }
    catch (const std::out_of_range& e) {
        return false;
    }
    return true;
}

void Diagnoza::Analiza_danych(Dane& dane, int liczba_uczacych_wierszy) {
    std::vector<double> mean_healthy(dane.liczba_kolumn - 1, 0.0);
    std::vector<double> mean_sick(dane.liczba_kolumn - 1, 0.0);
    int healthy_count = 0, sick_count = 0;

    for (int i = 0; i < liczba_uczacych_wierszy; ++i) {
        if (!isNumber(dane.dane[i][0])) continue;
        int is_sick = std::stoi(dane.dane[i][0]);
        for (int j = 1; j < dane.liczba_kolumn; ++j) {
            if (!isNumber(dane.dane[i][j])) continue;
            double value = std::stod(dane.dane[i][j]);
            if (is_sick) {
                mean_sick[j - 1] += value;
            }
            else {
                mean_healthy[j - 1] += value;
            }
        }
        if (is_sick) {
            ++sick_count;
        }
        else {
            ++healthy_count;
        }
        dane.Wyswietlanie_Procesu(i + 1, liczba_uczacych_wierszy);
    }

    for (int j = 0; j < dane.liczba_kolumn - 1; ++j) {
        mean_healthy[j] /= healthy_count;
        mean_sick[j] /= sick_count;
    }

    // Store these means for prediction
    dane.dane.push_back(std::vector<std::string>(dane.liczba_kolumn));
    dane.dane.push_back(std::vector<std::string>(dane.liczba_kolumn));
    for (int j = 0; j < dane.liczba_kolumn - 1; ++j) {
        dane.dane[dane.liczba_wierszy][j + 1] = std::to_string(mean_healthy[j]);
        dane.dane[dane.liczba_wierszy + 1][j + 1] = std::to_string(mean_sick[j]);
    }
}

void Diagnoza::Predykcja(Dane& dane) {
    std::vector<double> mean_healthy(dane.liczba_kolumn - 1, 0.0);
    std::vector<double> mean_sick(dane.liczba_kolumn - 1, 0.0);

    for (int j = 0; j < dane.liczba_kolumn - 1; ++j) {
        if (!isNumber(dane.dane[dane.liczba_wierszy][j + 1]) || !isNumber(dane.dane[dane.liczba_wierszy + 1][j + 1])) {
            std::cerr << "Invalid mean value detected.\n";
            return;
        }
        mean_healthy[j] = std::stod(dane.dane[dane.liczba_wierszy][j + 1]);
        mean_sick[j] = std::stod(dane.dane[dane.liczba_wierszy + 1][j + 1]);
    }

    int start_row = dane.dane.size() - 1;

    for (int i = start_row; i < dane.liczba_wierszy; ++i) {
        double score_healthy = 0.0, score_sick = 0.0;
        for (int j = 1; j < dane.liczba_kolumn; ++j) {
            if (!isNumber(dane.dane[i][j])) continue;
            double value = std::stod(dane.dane[i][j]);
            score_healthy += std::abs(value - mean_healthy[j - 1]);
            score_sick += std::abs(value - mean_sick[j - 1]);
        }
        dane.dane[i][0] = (score_healthy < score_sick) ? "0" : "1";
        dane.Wyswietlanie_Procesu(i - start_row + 1, dane.liczba_wierszy - start_row);
    }
}

double Diagnoza::Pomiar_Poprawnosci(const std::string& plik, const std::string& plik_wynikowy) {
    std::ifstream file(plik);
    std::ifstream file_wynikowy(plik_wynikowy);

    if (!file.is_open() || !file_wynikowy.is_open()) {
        std::cerr << "Nie można otworzyć pliku porównawczego lub wynikowego.\n";
        return -1.0;
    }

    std::string line, line_wynikowy;
    int total = 0;
    int correct = 0;

    while (std::getline(file, line) && std::getline(file_wynikowy, line_wynikowy)) {
        if (line == line_wynikowy) {
            ++correct;
        }
        ++total;
    }

    file.close();
    file_wynikowy.close();

    std::cout << "Poprawność predykcji: " << (static_cast<double>(correct) / total) * 100 << "%\n";
    return (static_cast<double>(correct) / total) * 100;
}
