#include "Wyniki.h"
#include <fstream>
#include <iostream>
#include <sstream> 

void Wyniki::Przedstawianie_wyniku(const std::vector<int>& predictions, const std::vector<std::vector<std::string>>& data, const std::vector<std::string>& columnNames, const std::string& outputFile) {
    std::ofstream outFile(outputFile);
    for (size_t j = 0; j < columnNames.size(); ++j) {
        outFile << columnNames[j];
        if (j < columnNames.size() - 1) {
            outFile << ",";
        }
    }
    outFile << std::endl;

    for (size_t i = 0; i < predictions.size(); ++i) {
        outFile << predictions[i];
        for (size_t j = 1; j < data.size(); ++j) {
            outFile << "," << data[j][i];
        }
        outFile << std::endl;
    }

    outFile.close();
    std::cout << "Wyniki zostały zapisane do " << outputFile << std::endl;
}

void Wyniki::Porownaj_Wyniki(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream inFile(inputFile);
    std::ifstream outFile(outputFile);

    if (!inFile.is_open() || !outFile.is_open()) {
        std::cerr << "Błąd: Nie można otworzyć pliku." << std::endl;
        return;
    }

    std::string inLine, outLine;
    int matchingCount = 0, totalCount = 0;

    // Skip headers
    std::getline(inFile, inLine);
    std::getline(outFile, outLine);

    while (std::getline(inFile, inLine) && std::getline(outFile, outLine)) {
        std::istringstream inStream(inLine);
        std::istringstream outStream(outLine); 

        std::string inResult, outResult;
        std::getline(inStream, inResult, ',');
        std::getline(outStream, outResult, ',');

        if (inResult == outResult) {
            matchingCount++;
        }
        totalCount++;
    }

    std::cout << "Liczba zgodnych wyników: " << matchingCount << " na " << totalCount << std::endl;
    inFile.close();
    outFile.close();
}
