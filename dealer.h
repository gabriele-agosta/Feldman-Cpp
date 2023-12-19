#ifndef DEALER_H
#define DEALER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
#include "polynomial.h"
#include "player.h"
#include "mod_pow.h"

class Dealer {
private:
    int threshold;
    std::vector<int> secret;
    int q;
    int p;
    int r;
    int g;
    std::vector<int> commitments;

public:
    Dealer(int threshold);
    int getQ();
    int getP();
    int getG();
    int getThreshold();
    std::vector<int> getSecret();
    std::vector<int> getCommitments();

    void chooseSecret();
    void chooseQ();
    void chooseP();
    void chooseGenerator();
    void distributeShares(std::vector<Player>& players, Polynomial& f);
    void distributeCommits(const std::vector<Player>& players);

private:
    bool isPrime(int n);
};

#endif // DEALER_H

