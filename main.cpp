#include <iostream>
#include <fstream>
#include <vector>
#include "mod_pow.h"
#include "player.h"
#include "dealer.h"
#include "polynomial.h"
#include <chrono>

using namespace std::chrono;

int delta(int i, const std::vector<int>& Xs, int q) {
    int d = 1;

    for (int j : Xs) {
        if (j != i) {
            d = (d * (-j) * mod_pow((i - j) % q, q - 2, q)) % q;
            if (d < 0) {
                d += q;
            }
        }
    }

    return d;
}


int reconstruct(const std::vector<Player>& players, int q) {
    int secretReconstructed = 0;
    std::vector<int> Xs;
    for (const Player& player : players) {
        Xs.push_back(player.getX());
    }
    for (const Player& player : players) {
        secretReconstructed += delta(player.getX(), Xs, q) * player.getY();
    }
    return secretReconstructed % q;
}

int main() {
    int threshold;
    std::cout << "Choose the threshold: ";
    std::cin >> threshold;

    Dealer dealer(threshold);

    dealer.chooseSecret();
    dealer.chooseQ();
    dealer.chooseP();
    dealer.chooseGenerator();

    int n;
    std::cout << "Choose the number of players: ";
    std::cin >> n;

    std::vector<Player> players;
    for (int i = 1; i <= n; i++) {
        players.push_back(Player(i));
    }

    auto start = high_resolution_clock::now();

    std::ofstream result("result.txt");
    for (int n_players = 1; n_players <= n; n_players++) {
        std::string reconstructedSecret = "";
        for (int cipher : dealer.getSecret()) {
            std::cout << "Q = " << dealer.getQ() << ", P = " << dealer.getP() << ", G = " << dealer.getG() << std::endl;
            Polynomial f(cipher, dealer.getQ(), dealer.getThreshold());
            f.printPolynomial();

            std::vector<Player> curr_players(players.begin(), players.begin() + n_players);
            dealer.distributeShares(curr_players, f);
            dealer.distributeCommits(curr_players);

            for (int i = 0; i < curr_players.size(); i++) {
                curr_players[i].verify(dealer.getG(), dealer.getP(), dealer.getThreshold(), f.getCoefficients());
                std::cout << "Dealer = " << dealer.getCommitments()[i] << ", Player" << i + 1 << " = " << curr_players[i].getVerification() << std::endl;
                if (curr_players[i].getVerification() == dealer.getCommitments()[i]) {
                    std::cout << "Player" << i + 1 << " share is verified" << std::endl;
                }
            }
            reconstructedSecret += static_cast<char>(reconstruct(curr_players, dealer.getQ()));
        }
        result << "Reconstructed secret with " << n_players << " shares = " << reconstructedSecret << std::endl;
    }
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);

    double seconds = duration.count() / 1e6;

    std::cout << seconds << " secondi" << std::endl;
    return 0;
}
