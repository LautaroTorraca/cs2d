//
// Created by lionel on 27/05/25.
//

#ifndef BUYER_H
#define BUYER_H
#include "Product.h"


class Buyer {
public:
    virtual ~Buyer() = default;

    virtual void buy(Product& product) = 0;
};


#endif  // BUYER_H
