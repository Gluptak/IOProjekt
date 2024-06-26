#include "dane.h"
#include "XLSHandler.h"
#include <iostream>



void Dane::wczytanie_danych(std::string file) {
    XLSHandler xlsHandler;
    auto data = xlsHandler.wczytaj_dane(file);
    
}

void Dane::wprowadzenie_danych(const std::vector<std::vector<std::string>>& data) {
    
}