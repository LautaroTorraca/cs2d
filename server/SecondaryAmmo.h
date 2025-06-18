//
// Created by lionel on 28/05/25.
//

#ifndef SECONDARYAMMO_H
#define SECONDARYAMMO_H
#include "Product.h"


class SecondaryAmmo : public Product {
    uint16_t amount;
public:
    SecondaryAmmo(const uint16_t& cost, const uint16_t& amount) : Product(cost*amount), amount(amount) {}
    void addTo(Inventory &inventory) override;
    ~SecondaryAmmo() override = default;
};



#endif //SECONDARYAMMO_H
