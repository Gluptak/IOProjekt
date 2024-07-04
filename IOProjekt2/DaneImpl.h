#pragma once
#ifndef DANEIMPL_H
#define DANEIMPL_H

#include "Dane.h"

class DaneImpl : public Dane {
public:
    void Wczytanie_Danych(const std::string& filename) override;
    void Wykrycie_Typow_Kolumn() override;
    void Pokaz_Typy_Kolumn() const override;
    void Pokaz_Progres_Wczytywania(size_t rowCount) const override;

    const std::vector<std::vector<std::string>>& Pobierz_Dane() const { return dane; }
    const std::vector<std::string>& Pobierz_Nazwy_Kolumn() const { return nazwyKolumn; }

private:
    bool jestLiczbaCalkowita(const std::string& s) const;
    bool jestLiczbaZmiennoprzecinkowa(const std::string& s) const;
};

#endif

