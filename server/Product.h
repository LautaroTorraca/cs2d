//
// Created by lionel on 12/05/25.
//

#ifndef PRODUCT_H
#define PRODUCT_H
#include "Addable.h"
#include "Wallet.h"

class Product: public Addable {
    uint16_t cost;

public:
    explicit Product(const uint16_t& cost): cost(cost) {}
    Product(Product&& other) noexcept;
    ~Product() override = default;
    void payWith(Wallet& wallet) const;
};

#endif  // PRODUCT_H
