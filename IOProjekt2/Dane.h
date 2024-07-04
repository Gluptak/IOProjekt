#ifndef DANE_H
#define DANE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <locale>
#include <codecvt>

class Dane {
public:
    virtual ~Dane() {}
    virtual void Wczytanie_Danych(const std::string& filename) = 0;
    virtual void Wykrycie_Typow_Kolumn() = 0;
    virtual void Pokaz_Typy_Kolumn() const = 0;
    virtual void Pokaz_Progres_Wczytywania(size_t rowCount) const = 0;

protected:
    std::vector<std::string> nazwyKolumn;
    std::vector<std::vector<std::string>> dane;
    std::map<std::string, std::string> typyKolumn;
};

#endif
