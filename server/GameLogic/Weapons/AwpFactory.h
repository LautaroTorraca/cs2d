//
// Created by lionel on 23/05/25.
//

#ifndef AWPFACTORY_H
#define AWPFACTORY_H
#include "GameLogic/Interfaces/Factory.h"
#include "GameLogic/Weapons/WeaponInformer.h"


class AwpFactory : public Factory {
    uint16_t cost;
    WeaponInformer& weaponsInfo;
public:
    explicit AwpFactory(const uint16_t cost, WeaponInformer& weaponsInfo) : cost(cost), weaponsInfo(weaponsInfo) {}
    std::unique_ptr<Product> getProduct(const uint16_t &amount) override;
};


#endif //AWPFACTORY_H
