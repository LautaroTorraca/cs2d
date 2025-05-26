#pragma once

#include <map>
#include <functional>
#include <memory>

#include "Orders/GameLobbyOrder.h"

class ServerGameLobby {
    std::map<OrderType, std::function<void(GameLobbyOrder&)>> translator;

    void setupTranslators();

public:

    ServerGameLobby();

    void handle(const std::unique_ptr<Order>& order) const;
};
