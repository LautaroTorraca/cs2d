#pragma once
#include "OrderType.h"


class Order {
public:
    virtual ~Order() = default;

    [[nodiscard]] virtual const OrderType& getOrderType() const = 0;
};
