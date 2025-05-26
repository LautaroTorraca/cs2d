#pragma once

#include <functional>
#include <map>
#include <memory>
#include "Orders/ServerLobbyOrder.h"

class ServerLobby {
    std::map<OrderType, std::function<void(ServerLobbyOrder&)>> translator;

    void setupTranslators();

public:

    ServerLobby();

    void handle(const std::unique_ptr<Order>& order) const;
};
