//
// Created by lionel on 28/05/25.
//

#ifndef SHOPPARSER_H
#define SHOPPARSER_H
#include <cstdint>
#include <functional>
#include <map>
#include <memory>
#include <string>

#include "Factory.h"
#include "ProductType.h"
#include "WeaponInformer.h"


class ShopParser {
    std::map<std::string, uint16_t> shopPrices;
    std::map<std::string, std::function<std::unique_ptr<Factory>(const uint16_t&, WeaponInformer&)>>
            factoryMaker;
    std::map<std::string, ProductType> typeTranslator;

public:
    explicit ShopParser(const std::string& shopFile);
    ShopParser(ShopParser&& other) noexcept;
    std::map<ProductType, std::unique_ptr<Factory>> getShopFactories(WeaponInformer& weaponsInfo);
};


#endif  // SHOPPARSER_H
