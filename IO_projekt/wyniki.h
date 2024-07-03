#ifndef WYNIKI_H
#define WYNIKI_H

#include <vector>
#include <string>

class Wyniki {
public:
    void Przedstawianie_wyniku(const std::vector<int>& predictions, const std::vector<std::vector<std::string>>& data, const std::vector<std::string>& columnNames, const std::string& outputFile);
    void Porownaj_Wyniki(const std::string& inputFile, const std::string& outputFile);
};

#endif
