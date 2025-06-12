//
// Created by lionel on 28/05/25.
//

#ifndef PRIMARYAMMO_H
#define PRIMARYAMMO_H
#include "Product.h"


class PrimaryAmmo: public Product {
    uint16_t amount;

public:
    PrimaryAmmo(const uint16_t& cost, const uint16_t& amount):
            Product(cost * amount), amount(amount) {}
    void addTo(Inventory& inventory) override;
    ~PrimaryAmmo() override = default;
};


#endif  // PRIMARYAMMO_H
