#include "ServerInGame.h"
#include <stdexcept>

ServerInGame::ServerInGame() {
    setupTranslators();
}

void ServerInGame::setupTranslators() {
    translator[IN_GAME_MOVE] = [](const InGameOrder& order) {
    };

    translator[IN_GAME_SHOOT] = [](const InGameOrder& order) {
    };

    translator[IN_GAME_PICK_UP_ITEM] = [](const InGameOrder& order) {
    };

    translator[IN_GAME_DROP_ITEM] = [](const InGameOrder& order) {
    };

    translator[IN_GAME_BUY_AMMO] = [](const InGameOrder& order) {
    };

    translator[IN_GAME_BUY_WEAPON] = [](const InGameOrder& order) {
    };

    translator[IN_GAME_SWITCH_WEAPON] = [](const InGameOrder& order) {
    };

    translator[IN_GAME_PLANT_BOMB] = [](const InGameOrder& order) {
    };

    translator[IN_GAME_DEFUSE_BOMB] = [](const InGameOrder& order) {
    };

    translator[IN_GAME_EXIT] = [](const InGameOrder& order) {
    };
}

void ServerInGame::handle(const std::unique_ptr<Order>& order) const {
    InGameOrder& inGameOrder = dynamic_cast<InGameOrder&>(*order);
    const OrderType type = inGameOrder.getOrderType();

    if (!translator.contains(type)) {
        throw -1; //TODO FIX
    }

    translator.at(type)(inGameOrder);
}
