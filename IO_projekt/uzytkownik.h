#pragma once
#ifndef UZYTKOWNIK_H
#define UZYTKOWNIK_H

#include <string>

class Uzytkownik {
public:
    std::string haslo;
    std::string imie;
    std::string nazwisko;
    int user_id;

    void logowanie(int, std::string, int, std::string);
    void rejestracja(std::string, std::string, std::string, int, std::string);
    void przypomnij_haslo(std::string);
};

#endif 
