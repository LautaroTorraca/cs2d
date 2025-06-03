#include "ServerInGame.h"
#include "Coordinate.h"
#include "GameParser.h"
#include "OpCodesConstans.h"

ServerInGame::ServerInGame()
    : gameParser("../maps/test_map.yaml", "../gameConstants/shop.yaml",
                 "../gameConstants/WeaponsConfig.yaml"),
      game(gameParser, 10) {
  setupTranslators();
}

void ServerInGame::setupTranslators() {
  translator[IN_GAME_MOVE] = [this](const InGameOrder &order) {
    Coordinate coordinate;
    switch (order.getDirection()) {
    case moveDown:
      coordinate.update(Coordinate(0, 1));
      break;
    case moveLeft:
      coordinate.update(Coordinate(-1, 0));
      break;
    case moveRight:
      coordinate.update(Coordinate(1, 0));
      break;
    case moveUp:
      coordinate.update(Coordinate(0, -1));
      break;
    }

    game.move(order.getPlayerId(), coordinate);
  };

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
