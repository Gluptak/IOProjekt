#pragma once
#ifndef DIAGNOZA_H
#define DIAGNOZA_H

#include <string>
#include <vector>
#include "dane.h"
#include "wynik.h"

class Diagnoza {
public:
    char wynik_diagnozy;

    void analiza_danych(const std::vector<std::vector<std::string>>& data, std::string method);
    void porownaj_diagnoze(std::string diagnoza1, std::string diagnoza2);
};

#endif 
