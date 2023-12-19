#include "player.h"

Player::Player(int x) {
   this->x = x;
   this->y = 0;
   this->verification = 0;
}

void Player::verify(int generator, int p, int threshold, const std::vector<int>& coefficients) {
    int res = 1;

    for (int i = 0; i < threshold; ++i) {
        res = (res * mod_pow(generator, coefficients[i] * std::pow(this->x, i), p)) % p;
    }
    this->verification = res;
}

int Player::getX() const { return this->x; }
int Player::getY() const { return this->y; }
int Player::getVerification() const { return verification; }

void Player::setY(int y) { this->y = y; }
