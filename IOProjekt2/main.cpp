#include <iostream>
#include <clocale>
#include "DaneImpl.h"
#include "Diagnoza.h"
#include "Wyniki.h"

void Wczytaj_Plik(std::string& filename, const std::string& prompt) {
    std::cout << prompt;
    std::cin >> filename;
}

void Wczytaj_i_Przygotuj_Dane(DaneImpl& dane, const std::string& filename, std::vector<std::vector<double>>& X, std::vector<int>& y) {
    dane.Wczytanie_Danych(filename);
    dane.Wykrycie_Typow_Kolumn();
    dane.Pokaz_Typy_Kolumn();

    const auto& dane_wczytane = dane.Pobierz_Dane();


    for (size_t i = 0; i < dane_wczytane[0].size(); ++i) {
        std::vector<double> features;
        for (size_t j = 1; j < dane_wczytane.size(); ++j) {
            features.push_back(std::stod(dane_wczytane[j][i]));
        }
        X.push_back(features);
        y.push_back(std::stoi(dane_wczytane[0][i]));
    }
}

int main() {
    std::locale::global(std::locale("")); 
    std::ios_base::sync_with_stdio(false);

    std::string naukaPlik, predykcjaPlik, porownaniePlik;
    Wczytaj_Plik(naukaPlik, "Podaj ścieżkę do pliku do nauki: ");
    Wczytaj_Plik(predykcjaPlik, "Podaj ścieżkę do pliku do predykcji: ");
    Wczytaj_Plik(porownaniePlik, "Podaj ścieżkę do pliku do porównania: ");

    DaneImpl dane;
    std::vector<std::vector<double>> X;
    std::vector<int> y;
    Wczytaj_i_Przygotuj_Dane(dane, naukaPlik, X, y);

    Diagnoza model(X[0].size());
    model.Analiza_danych(X, y, 1000, 0.01);

    dane.Wczytanie_Danych(predykcjaPlik);
    const auto& dane_predykcja = dane.Pobierz_Dane();
    std::vector<int> predictions;

    for (size_t i = 0; i < dane_predykcja[0].size(); ++i) {
        std::vector<double> features;
        for (size_t j = 1; j < dane_predykcja.size(); ++j) {
            features.push_back(std::stod(dane_predykcja[j][i]));
        }
        int prediction = model.Przewidywanie(features);
        predictions.push_back(prediction);
    }

    Wyniki wyniki;
    std::string outputFile = "predykcje.csv";
    wyniki.Przedstawianie_wyniku(predictions, dane_predykcja, dane.Pobierz_Nazwy_Kolumn(), outputFile);

    wyniki.Porownaj_Wyniki(porownaniePlik, outputFile);

    return 0;
}
