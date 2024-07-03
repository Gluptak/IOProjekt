#include "DaneImpl.h"

bool DaneImpl::jestLiczbaCalkowita(const std::string& s) const {
    std::istringstream iss(s);
    int x;
    return (iss >> x) && (iss.eof());
}

bool DaneImpl::jestLiczbaZmiennoprzecinkowa(const std::string& s) const {
    std::istringstream iss(s);
    double x;
    return (iss >> x) && (iss.eof());
}

void DaneImpl::Wczytanie_Danych(const std::string& filename) {
    std::wifstream file(filename);
    file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t>));

    if (!file.is_open()) {
        std::cerr << "Błąd: Nie można otworzyć pliku " << filename << std::endl;
        return;
    }

    std::wstring line;

    if (std::getline(file, line)) {
        std::wstringstream ss(line);
        std::wstring columnName;
        while (std::getline(ss, columnName, L',')) {
            nazwyKolumn.push_back(std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(columnName));
            dane.push_back({});
        }
    }

    size_t rowCount = 0;
    while (std::getline(file, line)) {
        std::wstringstream ss(line);
        std::wstring value;
        size_t colIndex = 0;
        while (std::getline(ss, value, L',')) {
            dane[colIndex].push_back(std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(value));
            colIndex++;
        }
        rowCount++;

        Pokaz_Progres_Wczytywania(rowCount);
    }
}


//Tu się coś psuje, out of range
void DaneImpl::Wykrycie_Typow_Kolumn() {
    for (size_t colIndex = 0; colIndex < nazwyKolumn.size(); colIndex++) {
        bool jestInt = true, jestDouble = true;
        for (const std::string& value : dane[colIndex]) {
            if (!jestLiczbaCalkowita(value)) {
                jestInt = false;
            }
            if (!jestLiczbaZmiennoprzecinkowa(value)) {
                jestDouble = false;
            }
            if (!jestInt && !jestDouble) {
                break;
            }
        }
        if (jestInt) {
            typyKolumn[nazwyKolumn[colIndex]] = "int";
        }
        else if (jestDouble) {
            typyKolumn[nazwyKolumn[colIndex]] = "double";
        }
        else {
            typyKolumn[nazwyKolumn[colIndex]] = "string";
        }
    }
}

void DaneImpl::Pokaz_Typy_Kolumn() const {
    std::cout << "Wykryte typy kolumn:" << std::endl;
    for (const auto& pair : typyKolumn) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}

void DaneImpl::Pokaz_Progres_Wczytywania(size_t rowCount) const {
    if (rowCount % 100 == 0) {
        std::wcout << L"Wczytano " << rowCount << L" wierszy..." << std::endl;
    }
}
