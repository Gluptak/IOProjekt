#include "wyniki.h"
#include <iostream>
#include <ctime>

void Wyniki::Przedstawianie_wyniku(Dane& dane, const std::string& katalog) {
    std::time_t now = std::time(nullptr);
    std::tm* ptm = std::localtime(&now);
    char buffer[32];
    // Generate file name based on current date and time
    std::strftime(buffer, 32, "%Y%m%d_%H%M%S.csv", ptm);
    std::string plik_wynikowy = katalog + "/" + buffer;

    dane.Zapisanie_Danych(plik_wynikowy);

    std::cout << "Wynik zapisany w: " << plik_wynikowy << "\n";
}
