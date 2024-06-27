#ifndef DIAGNOZA_H
#define DIAGNOZA_H

#include "dane.h"

class Diagnoza {
public:
    void Analiza_danych(Dane& dane, int liczba_uczacych_wierszy);
    void Predykcja(Dane& dane);
    double Pomiar_Poprawnosci(const std::string& plik, const std::string& plik_wynikowy);
};

#endif
