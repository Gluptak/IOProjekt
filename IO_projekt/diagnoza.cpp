#include "Diagnoza.h"
#include <cmath>

//Pierwszy lepszy algorytm, nie działa poprawnie, najpradopodobniej źle uzupełnia i odczytuje kolumny?

double Diagnoza::sigmoid(double z) const {
    return 1.0 / (1.0 + std::exp(-z));
}

double Diagnoza::iloczynSkalarny(const std::vector<double>& x1, const std::vector<double>& x2) const {
    double result = 0.0;
    for (size_t i = 0; i < x1.size(); ++i) {
        result += x1[i] * x2[i];
    }
    return result;
}

void Diagnoza::Analiza_danych(const std::vector<std::vector<double>>& X, const std::vector<int>& y, int epochs, double learningRate) {
    for (int epoch = 0; epoch < epochs; ++epoch) {
        for (size_t i = 0; i < X.size(); ++i) {
            std::vector<double> x = X[i];
            x.insert(x.begin(), 1.0); 
            double predicted = sigmoid(iloczynSkalarny(wagi, x));
            double error = y[i] - predicted;
            for (size_t j = 0; j < wagi.size(); ++j) {
                wagi[j] += learningRate * error * x[j];
            }
        }
    }
}

int Diagnoza::Przewidywanie(const std::vector<double>& x) {
    std::vector<double> xWithBias = x;
    xWithBias.insert(xWithBias.begin(), 1.0); 
    double probability = sigmoid(iloczynSkalarny(wagi, xWithBias));
    return probability >= 0.5 ? 1 : 0;
}
