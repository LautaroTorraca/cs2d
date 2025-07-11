//
// Created by lionel on 23/05/25.
//

#ifndef SHOP_H
#define SHOP_H
#include <map>

#include "Constants/ProductType.h"
#include "GameLogic/Interfaces/Factory.h"

#include "Buyer.h"

class Shop {
    std::map<ProductType, std::unique_ptr<Factory>> shopCatalog;
public:
    void add(const ProductType& type, std::unique_ptr<Factory>& factory);
    void buy(Buyer &buyer, const ProductType &productType);

    void buy(Buyer &buyer, const ProductType &productType, const uint16_t &amount);
};



#endif //SHOP_H
