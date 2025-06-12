//
// Created by lionel on 28/05/25.
//

#ifndef SECONDARYAMMOFACTORY_H
#define SECONDARYAMMOFACTORY_H
#include "Factory.h"


class SecondaryAmmoFactory: public Factory {
    uint16_t cost;

public:
    explicit SecondaryAmmoFactory(const uint16_t& cost): cost(cost) {}
    std::unique_ptr<Product> getProduct(const uint16_t& amount) override;
    ~SecondaryAmmoFactory() override = default;
};


#endif  // SECONDARYAMMOFACTORY_H
