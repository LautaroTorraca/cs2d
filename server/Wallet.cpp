//
// Created by lionel on 12/05/25.
//

#include "Wallet.h"
#include <stdexcept>

void Wallet::waste(const uint16_t& amount){
    if (amount > this->money){
        throw std::runtime_error("Not enough money"); //TODO: Reemplazar por una excepcion personalizada
    }
    this->money -= amount;
}

void Wallet::addMoney(const uint16_t &amount) {
    this->money += amount;
}

const uint16_t & Wallet::getInfo() {
    return this->money;
}
