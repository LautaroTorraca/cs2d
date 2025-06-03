#include "ServerInGame.h"

#define SHOP_PATH "../gameConstants/shop.yaml"
#define WEAPONS_INFO_PATH "../gameConstants/WeaponsConfig.yaml"

ServerInGame::ServerInGame(InGameProtocolInterface& protocol) : protocol(protocol) { setupTranslators(); }

void ServerInGame::setupTranslators() {

  this->movements.emplace(Movement::UP, Coordinate(0, -4));
  this->movements.emplace(Movement::DOWN, Coordinate(0, 4));
  this->movements.emplace(Movement::LEFT, Coordinate(-4, 0));
  this->movements.emplace(Movement::RIGHT, Coordinate(4, 0));
  this->movements.emplace(Movement::STAND, Coordinate(0, 0));

  translator[IN_GAME_MOVE] = [&](const InGameOrder & order) { this->move(order); };

  translator[IN_GAME_SHOOT] = [&](const InGameOrder &order) { this->attack(order); };

  translator[IN_GAME_PICK_UP_ITEM] = [&](const InGameOrder &order) { this->pickUp(order); };

  translator[IN_GAME_DROP_ITEM] = [](const InGameOrder &) {  return; };

  translator[IN_GAME_BUY_AMMO] = [&](const InGameOrder &order) { this->buyAmmo(order); };

  translator[IN_GAME_BUY_WEAPON] = [&](const InGameOrder &order) { this->buyWeapon(order); };

  translator[IN_GAME_SWITCH_WEAPON] = [&](const InGameOrder &order) { this->changeWeapon(order); };

  translator[IN_GAME_PLANT_BOMB] = [&](const InGameOrder &order) { this->plantBomb(order); };

  translator[IN_GAME_DEFUSE_BOMB] = [&](const InGameOrder &order) { this->defuseBomb(order); };

  translator[IN_GAME_EXIT] = [&](const InGameOrder &order) { this->exit(order); };
}

void ServerInGame::handle(const std::unique_ptr<Order> &order) const {
  InGameOrder &inGameOrder = dynamic_cast<InGameOrder &>(*order);
  const OrderType type = inGameOrder.getOrderType();

  if (!translator.contains(type)) {
    throw -1; // TODO FIX
  }

  translator.at(type)(inGameOrder);
}

void ServerInGame::addNewGame(std::string &gameName, const GameLobbyDTO &gameInfo) {
  GameParser parser(gameInfo.mapPath, SHOP_PATH, WEAPONS_INFO_PATH);
  Game game(parser, gameInfo.rounds);
  this->games.emplace(  std::piecewise_construct,
  std::forward_as_tuple(gameName),
  std::forward_as_tuple(parser, gameInfo.rounds));
  for (auto &playerChoices : gameInfo.playersChoices) {
    this->games.at(gameName).addPlayer(playerChoices.id, playerChoices.playerName, playerChoices.team, playerChoices.skin);
    this->playerToGame.emplace(playerChoices.id, gameName);
  }
  this->games.at(gameName).spawnBomb();

}

void ServerInGame::move(const InGameOrder &order) {
  std::string gameName = this->playerToGame.at(order.getPlayerId());
  Game& game = this->games.at(gameName);
  Coordinate& displacement = this->movements.at(order.getDirection());
  game.move(order.getPlayerId(), displacement);
}

void ServerInGame::attack(const InGameOrder &order) {
  std::string gameName = this->playerToGame.at(order.getPlayerId());
  Game& game = this->games.at(gameName);
  game.attack(order.getPlayerId());
}

void ServerInGame::pickUp(const InGameOrder &order) {
  std::string gameName = this->playerToGame.at(order.getPlayerId());
  Game& game = this->games.at(gameName);
  game.takeDrop(order.getPlayerId());
}

void ServerInGame::buyAmmo(const InGameOrder &order) {
  std::string gameName = this->playerToGame.at(order.getPlayerId());
  Game& game = this->games.at(gameName);
  game.buy(order.getPlayerId(), order.getProduct(), order.getAmmoAmount());
}

void ServerInGame::buyWeapon(const InGameOrder &order) {
  std::string gameName = this->playerToGame.at(order.getPlayerId());
  Game& game = this->games.at(gameName);
  game.buy(order.getPlayerId(), order.getProduct());
}

void ServerInGame::changeWeapon(const InGameOrder &order) {
  std::string gameName = this->playerToGame.at(order.getPlayerId());
  Game& game = this->games.at(gameName);
  game.setWeapon(order.getPlayerId(), order.getWeaponInformation());
}

void ServerInGame::plantBomb(const InGameOrder &order) {
  this->attack(order);
}

void ServerInGame::defuseBomb(const InGameOrder &order) {
  std::string gameName = this->playerToGame.at(order.getPlayerId());
  Game& game = this->games.at(gameName);
  game.deactivateBomb(order.getPlayerId());
}

void ServerInGame::exit(const InGameOrder &order) {
  this->protocol.disconnect({order.getPlayerId()});
}
