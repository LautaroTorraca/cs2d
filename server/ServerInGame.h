#pragma once

#include <map>
#include <functional>
#include <memory>

#include "Orders/InGameOrder.h"

class ServerInGame {
    std::map<OrderType, std::function<void(InGameOrder&)>> translator;

    void setupTranslators();

public:

    ServerInGame();

    void handle(const std::unique_ptr<Order>& order) const;
};
