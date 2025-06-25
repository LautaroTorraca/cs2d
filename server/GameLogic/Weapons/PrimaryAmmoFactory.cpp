//
// Created by lionel on 28/05/25.
//

#include "PrimaryAmmoFactory.h"

#include "PrimaryAmmo.h"

std::unique_ptr<Product> PrimaryAmmoFactory::getProduct(const uint16_t &amount) {
    return std::make_unique<PrimaryAmmo>(this->cost, amount);
}
