//
// Created by lionel on 12/05/25.
//

#include "Wallet.h"

#include <stdexcept>

#include "NotEnoughMoneyException.h"

void Wallet::waste(const uint16_t& amount){
    if (amount > this->money){
        throw NotEnoughMoneyException("Not enough money");
    }
    this->money -= amount;
}

void Wallet::addMoney(const uint16_t &amount) {
    this->money += amount;
}

void Wallet::wasteAll() {
    this->money = 0;
}

const uint16_t & Wallet::getInfo() {
    return this->money;
}
