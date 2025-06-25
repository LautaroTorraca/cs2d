//
// Created by lionel on 03/06/25.
//

#ifndef BUYORDER_H
#define BUYORDER_H
#include "common/Constants/ProductType.h"

#define DEFAULT_AMOUNT 1

struct BuyOrder {
    const ProductType type;
    const uint16_t amount;
    BuyOrder(const ProductType& type, const uint16_t& amount): type(type), amount(amount) {}
    explicit BuyOrder(const ProductType& type): type(type), amount(DEFAULT_AMOUNT) {}
};

#endif  // BUYORDER_H
