//
// Created by lionel on 23/05/25.
//

#include "Shop.h"

#define DEFAULT_AMOUNT 1

void Shop::add(const ProductTypes &type, std::unique_ptr<Factory> &factory) {
    this->shopCatalog.emplace(type, std::move(factory));
}

void Shop::buy(Buyer &buyer, const ProductTypes &productType) {
    this->buy(buyer, productType, DEFAULT_AMOUNT);
}

void Shop::buy(Buyer &buyer, const ProductTypes &productType, const uint16_t& amount) {
    if (this->shopCatalog.contains(productType)) {
        std::unique_ptr<Product> product = this->shopCatalog.at(productType)->getProduct(amount);
        buyer.buy(*product);
    }
}
