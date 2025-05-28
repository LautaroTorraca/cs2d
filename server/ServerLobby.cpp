#include "ServerLobby.h"
#include <stdexcept>

ServerLobby::ServerLobby() {
    setupTranslators();
}

void ServerLobby::setupTranslators() {
    translator[LOBBY_CREATE] = [](const ServerLobbyOrder& order) {
        return;
    };

    translator[LOBBY_LIST] = [](const ServerLobbyOrder& order) {
        return;
    };

    translator[LOBBY_JOIN] = [](const ServerLobbyOrder& order) {
        return;
    };

    translator[LOBBY_DISCONNECT] = [](const ServerLobbyOrder& order) {
        return;
    };
}

void ServerLobby::handle(const std::unique_ptr<Order>& order) const {
    ServerLobbyOrder& lobbyOrder = dynamic_cast<ServerLobbyOrder&>(*order);
    const OrderType type = lobbyOrder.getOrderType();

    if (!translator.contains(type)) {
        throw -1; //TODO FIX
    }

    translator.at(type)(lobbyOrder);
}

