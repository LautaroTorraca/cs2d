//
// Created by lionel on 24/05/25.
//

#ifndef M3FACTORY_H
#define M3FACTORY_H

#include "Factory.h"
#include "Product.h"
#include "WeaponInformer.h"

class M3Factory: public Factory {
    uint16_t cost;
    WeaponInformer& weaponsInfo;

public:
    explicit M3Factory(const uint16_t cost, WeaponInformer& weaponsInfo):
            cost(cost), weaponsInfo(weaponsInfo) {}
    std::unique_ptr<Product> getProduct(const uint16_t& amount) override;
};


#endif  // M3FACTORY_H
