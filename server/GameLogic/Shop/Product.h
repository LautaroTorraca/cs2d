//
// Created by lionel on 12/05/25.
//

#ifndef PRODUCT_H
#define PRODUCT_H
#include "GameLogic/Interfaces/Addable.h"

#include "Wallet.h"

class Product : public Addable{
    uint16_t cost;
public:

    explicit Product(const uint16_t& cost): cost(cost) {}
    Product(Product&& other) noexcept;
    ~Product() override = default;
    void payWith(Wallet& wallet) const;
    void reintegrateTo(Wallet& wallet);
};

#endif //PRODUCT_H
