#pragma once
#ifndef DANE_H
#define DANE_H

#include <string>
#include <vector>

class Dane {
public:
    std::vector<std::vector<std::string>> dane_pacjenta;
    std::string tabela_danych;

    void wczytanie_danych(std::string file);
    void wprowadzenie_danych(const std::vector<std::vector<std::string>>& data);
};

#endif
