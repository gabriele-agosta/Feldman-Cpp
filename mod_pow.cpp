#include "mod_pow.h"

int mod_pow(long long base, long long exponent, long long modulus) {
    int result = 1;
    base = base % modulus;

    while (exponent > 0) {
        if (exponent & 1) {
            result = (result * base) % modulus;
        }
        base = (base * base) % modulus;
        exponent = exponent >> 1;
    }

    return result;
}
