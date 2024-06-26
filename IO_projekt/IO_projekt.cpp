#include <iostream>
#include "uzytkownik.h"
#include "dane.h"
#include "diagnoza.h"
#include "wynik.h"
#include "XLSHandler.h"

int main() {
    Uzytkownik user;
    Dane dane;
    Diagnoza diagnoza;
    Wynik wynik;

    // Pseudo konfiguracja interfejsu graficznego
    std::cout << "Konfiguracja interfejsu graficznego." << std::endl;
    std::cout << "Wczytanie czcionek oraz grafiki interfejsu graficznego." << std::endl;

    // Załadowanie danych 
    std::cout << "Zaladownie danych z zewnetrznego pliku." << std::endl;
    dane.wczytanie_danych("data/patients_data.xlsx");

    // Dane wejściowe
    std::cout << "Uzupelnienie wczytanych danych." << std::endl;
    dane.wprowadzenie_danych(dane.dane_pacjenta);

    // Analiza danych 
    std::cout << "Przeanalizowanie danych oraz uzupelnienie werdyktow." << std::endl;
    diagnoza.analiza_danych(dane.dane_pacjenta, "some method");

    // Wyświetlenie danych przeanalizowanych
    std::cout << "Wyswietlenie danych lub przekazanie ich do innego pliku." << std::endl;
    wynik.przedstawienie_wyniku(dane.dane_pacjenta);


    // Odświerzenie programu lub jego zakmnięcie
    char refresh;
    std::cout << "Czy odswiezyc dane? (t/n): ";
    std::cin >> refresh;
    if (refresh == 't' || refresh == 'T') {
        }
    else {
        char close;
        std::cout << "Czy zamknac program? (t/n): ";
        std::cin >> close;
        if (close == 't' || close == 'T') {
            std::cout << "Koniec Programu" << std::endl;
            return 0;
        }
    }

    return 0;
}