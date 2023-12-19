#include "dealer.h"

Dealer::Dealer(int threshold) {
    this->threshold = threshold;
    q = 0;
    p = 0;
    r = 0;
    g = 0;
}

int Dealer::getQ() { return this->q; }

int Dealer::getP() { return this->p; }

int Dealer::getG() { return this->g; }

int Dealer::getThreshold() { return this->threshold; }

std::vector<int> Dealer::getCommitments() { return this->commitments; }

std::vector<int> Dealer::getSecret() { return this->secret; }

//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

void Dealer::chooseSecret() {
    int choice;

    while (true) {
        std::cout << "Choose what you want to encrypt:\n1. Text/Number\n2. File content\n";
        std::cin >> choice;

        if ((choice == 1 || choice == 2)) {
            break;
        }
    }

    std::vector<int> asciiSecret;

    if (choice == 1) {
        std::cout << "Insert your secret: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        for (char c; std::cin.get(c) && c != '\n'; ) {
            asciiSecret.push_back(static_cast<int>(c));
        }
    } else {
        std::ifstream file("secret.txt");

        if (file.is_open()) {
            file.seekg(0, std::ios::end);
            size_t file_size = file.tellg();
            file.seekg(0, std::ios::beg);

            asciiSecret.reserve(file_size);

            for (char c; file.get(c); ) {
                asciiSecret.push_back(static_cast<int>(c));
            }

            file.close();
        } else {
            std::cerr << "Unable to open file" << std::endl;
        }
    }

    this->secret = std::move(asciiSecret);
}


void Dealer::chooseQ() {
    this->q = 127;
}

void Dealer::chooseP() {
    int r = 1;
    int p = r * this->q + 1;

    while (!isPrime(p)) {
        r++;
        p = r * this->q + 1;
    }

    this->p = p;
    this->r = r;
}

void Dealer::chooseGenerator() {
    std::vector<int> G;

    for (int i = 1; i < this->p; ++i) {
        if (std::gcd(i, this->p) == 1) {
            int candidate = static_cast<int>(pow(i, this->r)) % this->p;
            G.push_back(candidate);
        }
    }

    std::sort(G.begin(), G.end());
    G.erase(std::unique(G.begin(), G.end()), G.end());

    while (true) {
        int randomIndex = rand() % G.size();
        int g = G[randomIndex];

        if (g != 1) {
            this->g = g;
            break;
        }
    }
}


void Dealer::distributeShares(std::vector<Player>& players, Polynomial& f) {
    for (Player& player : players) {
        player.setY(f.computePolynomial(player.getX(), this->q));
    }
}

void Dealer::distributeCommits(const std::vector<Player>& players) {
    std::vector<int> commitments;
    commitments.reserve(players.size());

    for (const Player& player : players) {
        commitments.emplace_back(mod_pow(this->g, player.getY(), this->p) % this->p);
    }

    this->commitments = commitments;
}

bool Dealer::isPrime(int n) {
    if (n == 2) {
        return true;
    }
    if (n == 1 || n % 2 == 0) {
        return false;
    }
    int i = 3;
    while (i <= std::sqrt(n)) {
        if (n % i == 0) {
            return false;
        }
        i += 2;
    }
    return true;
}
