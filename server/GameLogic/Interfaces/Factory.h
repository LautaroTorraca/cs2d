//
// Created by lionel on 23/05/25.
//

#ifndef FACTORY_H
#define FACTORY_H
#include <memory>

#include "GameLogic/Shop/Product.h"

class Factory {
    public:
    virtual ~Factory() = default;

    virtual std::unique_ptr<Product> getProduct(const uint16_t &amount) = 0;
};

#endif //FACTORY_H
