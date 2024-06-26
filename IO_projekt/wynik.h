#pragma once
#ifndef WYNIK_H
#define WYNIK_H

#include <vector>
#include <string>

class Wynik {
public:
    double tabela;
    std::vector<int> wykres;
    std::vector<int> zdjecie;

    void przedstawienie_wyniku(const std::vector<std::vector<std::string>>& data);
    void pobierz_wyniki();
    void grupuj();
    void sortuj();
};

#endif 