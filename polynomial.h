#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <cmath>
#include <vector>
#include <ctime>
#include "mod_pow.h"

class Polynomial {
private:
    int order;
    std::vector<int> coefficients;

public:
    Polynomial(int secret, int q, int threshold);
    std::vector<int>getCoefficients();
    void computeCoefficients(int q, int order);
    int computePolynomial(int x, int q);
    void printPolynomial();
};

#endif // POLYNOMIAL_H

