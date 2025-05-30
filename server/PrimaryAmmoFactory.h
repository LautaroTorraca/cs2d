//
// Created by lionel on 28/05/25.
//

#ifndef PRIMARYAMMOFACTORY_H
#define PRIMARYAMMOFACTORY_H
#include "Factory.h"


class PrimaryAmmoFactory : public Factory{
    uint16_t cost;
public:
    explicit PrimaryAmmoFactory(const uint16_t& cost) : cost(cost){}
    std::unique_ptr<Product> getProduct(const uint16_t &amount) override;
    ~PrimaryAmmoFactory() override = default;
};



#endif //PRIMARYAMMOFACTORY_H
