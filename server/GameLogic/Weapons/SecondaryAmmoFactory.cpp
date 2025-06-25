//
// Created by lionel on 28/05/25.
//

#include "SecondaryAmmoFactory.h"

#include "SecondaryAmmo.h"

std::unique_ptr<Product> SecondaryAmmoFactory::getProduct(const uint16_t &amount) {
    return std::make_unique<SecondaryAmmo>(this->cost, amount);
}
