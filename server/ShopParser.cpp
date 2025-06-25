//
// Created by lionel on 28/05/25.
//

#include "ShopParser.h"

#include <fstream>

#include <fkYAML/node.hpp>

#include "GameLogic/Weapons/AKFactory.h"
#include "GameLogic/Weapons/AwpFactory.h"
#include "GameLogic/Weapons/M3Factory.h"
#include "GameLogic/Weapons/PrimaryAmmoFactory.h"
#include "GameLogic/Weapons/SecondaryAmmoFactory.h"

#define PRICES_KEY "productsPrices"
#define AK_KEY "ak"
#define M3_KEY "m3"
#define AWP_KEY "awp"
#define PRIMARY_AMMO_KEY "primaryAmmo"
#define SECONDARY_AMMO_KEY "secondaryAmmo"

ShopParser::ShopParser(const std::string &shopFile) {
    std::ifstream file(shopFile.c_str());
    fkyaml::node root = fkyaml::node::deserialize(file);
    this->shopPrices = root[PRICES_KEY].get_value<std::map<std::string, uint16_t>>();
    this->factoryMaker.emplace(AK_KEY, [&](const uint16_t& price, WeaponInformer& weaponsInfo)->std::unique_ptr<Factory>{return std::move(std::make_unique<AKFactory>(price, weaponsInfo));});
    this->factoryMaker.emplace(M3_KEY, [&](const uint16_t& price, WeaponInformer& weaponsInfo)->std::unique_ptr<Factory>{return std::move(std::make_unique<M3Factory>(price, weaponsInfo));});
    this->factoryMaker.emplace(AWP_KEY, [&](const uint16_t& price, WeaponInformer& weaponsInfo)->std::unique_ptr<Factory>{return std::move(std::make_unique<AwpFactory>(price, weaponsInfo));});
    this->factoryMaker.emplace(PRIMARY_AMMO_KEY, [&](const uint16_t& price, WeaponInformer&)->std::unique_ptr<Factory>{ return std::move(std::make_unique<PrimaryAmmoFactory>(price));});
    this->factoryMaker.emplace(SECONDARY_AMMO_KEY, [&](const uint16_t& price, WeaponInformer&)->std::unique_ptr<Factory>{ return std::move(std::make_unique<SecondaryAmmoFactory>(price));});

    this->typeTranslator.emplace(AK_KEY, ProductType::AK_47_WEAPON);
    this->typeTranslator.emplace(M3_KEY, ProductType::M3_WEAPON);
    this->typeTranslator.emplace(AWP_KEY, ProductType::AWP_WEAPON);
    this->typeTranslator.emplace(PRIMARY_AMMO_KEY, ProductType::PRIMARY_AMMO);
    this->typeTranslator.emplace(SECONDARY_AMMO_KEY, ProductType::SECONDARY_AMMO);
}

ShopParser::ShopParser(ShopParser &&other) noexcept : shopPrices(std::move(other.shopPrices)), factoryMaker(std::move(other.factoryMaker)), typeTranslator(std::move(other.typeTranslator)) {
    if (this != &other) {
        other.shopPrices = std::map<std::string, uint16_t>();
        other.factoryMaker = std::map<std::string, std::function<std::unique_ptr<Factory>(const uint16_t&, WeaponInformer&)>>();
        other.typeTranslator = std::map<std::string, ProductType>();
    }
}

std::map<ProductType, std::unique_ptr<Factory>> ShopParser::getShopFactories(WeaponInformer& weaponsInfo) {
    std::map<ProductType, std::unique_ptr<Factory>> shopFactories;
    for (const auto &[productName, price] : this->shopPrices) {
            ProductType type = this->typeTranslator.at(productName);
            shopFactories.emplace(type, std::move(this->factoryMaker.at(productName)(price, weaponsInfo)));
        }
    return shopFactories;
}

std::map<ProductType, double> ShopParser::getProductsPrices() {
    std::map<ProductType, double> productsPrices;
    for (const auto &[productName, price] : this->shopPrices) {
        ProductType type = this->typeTranslator.at(productName);
        productsPrices.emplace(type, price);
    }
    return productsPrices;
}
