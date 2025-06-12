//
// Created by lionel on 12/05/25.
//

#ifndef WALLET_H
#define WALLET_H
#include <cstdint>


class Wallet {
    uint16_t money;
public:
    Wallet(const uint16_t& money): money(money) {}
    void waste(const uint16_t& amount);
    void addMoney(const uint16_t& amount);
    void wasteAll();

    const uint16_t & getInfo();
};



#endif //WALLET_H
