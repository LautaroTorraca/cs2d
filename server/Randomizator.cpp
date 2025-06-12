//
// Created by lionel on 19/05/25.
//

#include "Randomizator.h"

#include <random>

int Randomizator::getRandom(const int& min, const int& max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(min, max);
    int num = distrib(gen);
    return num;
}

int Randomizator::getRandom(const int& max) { return this->getRandom(0, max); }
