#ifndef DANE_H
#define DANE_H

#include <vector>
#include <string>

class Dane {
public:
    virtual void Wczytanie_Danych(const std::string& plik) = 0;
    virtual void Zapisanie_Danych(const std::string& plik) = 0;
    virtual void Wyswietlanie_Procesu(int obecny, int calkowity) = 0;

    std::vector<std::vector<std::string>> dane;
    int liczba_wierszy;
    int liczba_kolumn;
};

class DaneImpl : public Dane {
public:
    void Wczytanie_Danych(const std::string& plik) override;
    void Zapisanie_Danych(const std::string& plik) override;
    void Wyswietlanie_Procesu(int obecny, int calkowity) override;
};

#endif
