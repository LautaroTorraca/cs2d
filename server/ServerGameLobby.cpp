#include "ServerGameLobby.h"
#include <stdexcept>

ServerGameLobby::ServerGameLobby() {
    setupTranslators();
}

void ServerGameLobby::setupTranslators() {
    translator[GAME_LOBBY_READY] = [](const GameLobbyOrder& order) {
    };

    translator[GAME_LOBBY_EXIT] = [](const GameLobbyOrder& order) {
    };
}

void ServerGameLobby::handle(const std::unique_ptr<Order>& order) const {
    GameLobbyOrder& gameLobbyOrder = dynamic_cast<GameLobbyOrder&>(*order);
    OrderType type = gameLobbyOrder.getOrderType();

    if (!translator.contains(type)) {
        throw -1; //TODO FIX
    }

    translator.at(type)(gameLobbyOrder);
}
