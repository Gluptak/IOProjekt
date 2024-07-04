#pragma once
#ifndef DIAGNOZA_H
#define DIAGNOZA_H

#include <vector>

class Diagnoza {
public:
    Diagnoza(int numFeatures) : wagi(numFeatures + 1, 0.0) {}
    void Analiza_danych(const std::vector<std::vector<double>>& X, const std::vector<int>& y, int epochs, double learningRate);
    int Przewidywanie(const std::vector<double>& x);

private:
    std::vector<double> wagi;

    double sigmoid(double z) const;
    double iloczynSkalarny(const std::vector<double>& x1, const std::vector<double>& x2) const;
};

#endif
