//
// Created by lionel on 23/05/25.
//

#ifndef SHOP_H
#define SHOP_H
#include <map>

#include "Buyer.h"
#include "ProductTypes.h"
#include "Factory.h"

class Shop {
    std::map<ProductTypes, std::unique_ptr<Factory>> shopCatalog;
public:
    void add(const ProductTypes& type, std::unique_ptr<Factory>& factory);
    void buy(Buyer &buyer, const ProductTypes &productType);

    void buy(Buyer &buyer, const ProductTypes &productType, const uint16_t &amount);
};



#endif //SHOP_H
