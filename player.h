#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <cmath>
#include "mod_pow.h"

class Player {
private:
    int x;
    int y;
    int verification;

public:
    Player(int x);

    void verify(int generator, int p, int threshold, const std::vector<int>& coefficients);

    // Aggiungi eventuali getter e setter necessari
    int getX() const;
    int getY() const;
    int getVerification() const;

    void setY(int y);
};

#endif // PLAYER_H
