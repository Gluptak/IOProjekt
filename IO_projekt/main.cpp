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
    std::cout << "Wczytywanie danych z pliku: " << filename << std::endl;
    dane.Wczytanie_Danych(filename);
    dane.Wykrycie_Typow_Kolumn();
    dane.Pokaz_Typy_Kolumn();

    const auto& dane_wczytane = dane.Pobierz_Dane();

    if (dane_wczytane.empty() || dane_wczytane[0].empty()) {
        std::cerr << "Błąd: Plik nie zawiera danych." << std::endl;
        return;
    }

    std::cout << "Przygotowywanie danych treningowych." << std::endl;

    for (size_t i = 0; i < dane_wczytane[0].size(); ++i) {
        std::vector<double> features;
        for (size_t j = 1; j < dane_wczytane.size(); ++j) {
            features.push_back(std::stod(dane_wczytane[j][i]));
        }
        X.push_back(features);
        y.push_back(std::stoi(dane_wczytane[0][i]));
    }
    std::cout << "Dane treningowe zostały przygotowane." << std::endl;
}


//Oczywiście polskie znaki nie działają, nie wiem co jest nie tak
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

   
    if (X.empty() || y.empty()) {
        std::cerr << "Błąd: Brak danych treningowych." << std::endl;
        return 1;
    }

    std::cout << "Trenowanie modelu..." << std::endl;
    
    Diagnoza model(X[0].size());
    model.Analiza_danych(X, y, 1000, 0.01);

    std::cout << "Wczytywanie danych do predykcji z pliku: " << predykcjaPlik << std::endl;
   
    dane.Wczytanie_Danych(predykcjaPlik);
    const auto& dane_predykcja = dane.Pobierz_Dane();
    std::vector<int> predictions;

    
    if (dane_predykcja.empty() || dane_predykcja[0].empty()) {
        std::cerr << "Błąd: Brak danych do predykcji." << std::endl;
        return 1;
    }

    std::cout << "Liczba kolumn: " << dane_predykcja.size() << ", liczba wierszy: " << dane_predykcja[0].size() << std::endl;

    std::cout << "Przewidywanie wyników..." << std::endl;
   
    for (size_t i = 0; i < dane_predykcja[0].size(); ++i) {
        std::vector<double> features;
        for (size_t j = 1; j < dane_predykcja.size(); ++j) {
            std::string value = dane_predykcja[j][i];
            std::cout << "Przetwarzanie wartości: " << value << " w kolumnie " << j << " i wierszu " << i << std::endl;
            try {
                features.push_back(std::stod(value));
            }
            catch (const std::invalid_argument& e) {
                std::cerr << "Błąd: Nie można przekonwertować wartości " << value << " na double." << std::endl;
                return 1;
            }
            catch (const std::out_of_range& e) {
                std::cerr << "Błąd: Wartość " << value << " jest poza zakresem dla double." << std::endl;
                return 1;
            }
        }
        int prediction = model.Przewidywanie(features);
        predictions.push_back(prediction);
    }

  
    Wyniki wyniki;
    std::string outputFile = "predykcje.csv";
    wyniki.Przedstawianie_wyniku(predictions, dane_predykcja, dane.Pobierz_Nazwy_Kolumn(), outputFile);

    std::cout << "Porównywanie wyników..." << std::endl;
   
    wyniki.Porownaj_Wyniki(porownaniePlik, outputFile);

    std::cout << "Program zakończył działanie." << std::endl;
    return 0;
}
