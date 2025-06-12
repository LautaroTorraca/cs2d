//
// Created by lionel on 27/05/25.
//
#include "Product.h"

Product::Product(Product &&other) noexcept : cost(other.cost){
    if ( this != &other ) {
        other.cost = 0;
    }
}

void Product::payWith(Wallet& wallet) const {
    wallet.waste(this->cost);
}
