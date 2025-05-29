#include "ServerInGame.h"

ServerInGame::ServerInGame() { setupTranslators(); }

void ServerInGame::setupTranslators() {
  translator[IN_GAME_MOVE] = [](const InGameOrder &) {};

  translator[IN_GAME_SHOOT] = [](const InGameOrder &) {};

  translator[IN_GAME_PICK_UP_ITEM] = [](const InGameOrder &) {};

  translator[IN_GAME_DROP_ITEM] = [](const InGameOrder &) {};

  translator[IN_GAME_BUY_AMMO] = [](const InGameOrder &) {};

  translator[IN_GAME_BUY_WEAPON] = [](const InGameOrder &) {};

  translator[IN_GAME_SWITCH_WEAPON] = [](const InGameOrder &) {};

  translator[IN_GAME_PLANT_BOMB] = [](const InGameOrder &) {};

  translator[IN_GAME_DEFUSE_BOMB] = [](const InGameOrder &) {};

  translator[IN_GAME_EXIT] = [](const InGameOrder &) {};
}

void ServerInGame::handle(const std::unique_ptr<Order> &order) const {
  InGameOrder &inGameOrder = dynamic_cast<InGameOrder &>(*order);
  const OrderType type = inGameOrder.getOrderType();

  if (!translator.contains(type)) {
    throw -1; // TODO FIX
  }

  translator.at(type)(inGameOrder);
}
