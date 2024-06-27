#define _CRT_SECURE_NO_DEPRECATE

#include "dane.h"
#include "diagnoza.h"
#include "wyniki.h"
#include <iostream>
#include <string>

int main() {
    DaneImpl dane;
    Diagnoza diagnoza;
    Wyniki wyniki;

    std::string plik_wejsciowy, katalog_wyjsciowy, plik_porownawczy;
    int liczba_uczacych_wierszy;

    std::cout << "\nPodaj nazwę pliku wejściowego: \n";
    std::cin >> plik_wejsciowy;
    dane.Wczytanie_Danych(plik_wejsciowy);

    std::cout << "\nPodaj liczbę uczących wierszy: \n";
    std::cin >> liczba_uczacych_wierszy;
    diagnoza.Analiza_danych(dane, liczba_uczacych_wierszy);

    std::cout << "\nPodaj katalog wyjściowy do zapisania wyników: \n";
    std::cin >> katalog_wyjsciowy;
    wyniki.Przedstawianie_wyniku(dane, katalog_wyjsciowy);

    std::cout << "\nPodaj nazwę pliku porównawczego: \n";
    std::cin >> plik_porownawczy;
    double accuracy = diagnoza.Pomiar_Poprawnosci(plik_porownawczy, katalog_wyjsciowy + "/" + "your_generated_file_name");
    if (accuracy >= 0) {
        std::cout << "Poprawność predykcji: " << accuracy << "%\n";
    }

    return 0;
}
