#include "polynomial.h"

Polynomial::Polynomial(int secret, int q, int threshold) {
    this->order = threshold - 1;
    this->coefficients.reserve(threshold);
    this->coefficients.push_back(secret);

    computeCoefficients(q, order);
}

std::vector<int> Polynomial::getCoefficients() { return this->coefficients; }

void Polynomial::computeCoefficients(int q, int order) {
    std::srand(std::time(0));

    for (int i = 0; i < order; ++i) {
        this->coefficients.push_back(std::rand() % q + 1);
    }
}

int Polynomial::computePolynomial(int x, int q) {
    int res = 0;
    for (int i = 0; i <= order; ++i) {
        int term = mod_pow(x, i, q);
        res = (res + coefficients[i] * term) % q;
    }
    return res;
}

void Polynomial::printPolynomial() {
    for (int i = 0; i < order; ++i) {
        std::cout << coefficients[i] << "x^" << i << " + ";
    }
    std::cout << coefficients[order] << "x^" << this->order << std::endl;
}

