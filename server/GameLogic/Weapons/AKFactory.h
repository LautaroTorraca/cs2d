//
// Created by lionel on 23/05/25.
//

#ifndef AKFACTORY_H
#define AKFACTORY_H
#include "GameLogic/Interfaces/Factory.h"

#include "Ak.h"
#include "WeaponInformer.h"

class AKFactory : public Factory {
    uint16_t cost;
    WeaponInformer& weaponsInfo;
public:
    explicit AKFactory(const uint16_t cost, WeaponInformer& weaponsInfo) : cost(cost), weaponsInfo(weaponsInfo) {}
    std::unique_ptr<Product> getProduct(const uint16_t &amount) override;
};



#endif //AKFACTORY_H
