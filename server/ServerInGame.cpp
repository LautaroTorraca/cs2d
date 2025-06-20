#include "ServerInGame.h"

#include <ranges>

#include "Monitor/GameMonitor.h"

#define SHOP_PATH "../gameConstants/shop.yaml"
#define WEAPONS_INFO_PATH "../gameConstants/WeaponsConfig.yaml"

ServerInGame::ServerInGame(InGameProtocolInterface& protocol) : protocol(protocol) {
    setupTranslators();
    this->eraserThread = std::thread(&ServerInGame::erase, this);
}

void ServerInGame::setupTranslators() {

  this->movements.emplace(Movement::UP, Coordinate(0, -4));
  this->movements.emplace(Movement::RIGHT, Coordinate(4, 0));
  this->movements.emplace(Movement::DOWN, Coordinate(0, 4));
  this->movements.emplace(Movement::LEFT, Coordinate(-4, 0));
  this->movements.emplace(Movement::STAND, Coordinate(0, 0));

  translator[IN_GAME_MOVE] = [&](const InGameOrder & order) { this->move(order); };

  translator[IN_GAME_SHOOT] = [&](const InGameOrder &order) { this->attack(order); };

  translator[IN_GAME_PICK_UP_ITEM] = [&](const InGameOrder &order) { this->pickUp(order); };

  translator[IN_GAME_DROP_ITEM] = [](const InGameOrder &) {  return; };

  translator[IN_GAME_BUY] = [&](const InGameOrder &order) { this->buy(order); };

  translator[IN_GAME_CHANGE_ANGLE] = [&](const InGameOrder &order) { this->changeAngle(order); };

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
  this->games.emplace(gameName, std::make_shared<GameMonitor>(gameName, parser, gameInfo.rounds, this->protocol, this->gamesToErase));
  for (auto &playerChoices : gameInfo.playersChoices) {
    this->games.at(gameName)->addPlayer(playerChoices.id, playerChoices.playerName, playerChoices.team, playerChoices.skin);
    this->playerToGame.emplace(playerChoices.id, gameName);
  }
  this->games.at(gameName)->spawnBomb();
  this->games.at(gameName)->start();
}

void ServerInGame::leaveGameLobby(const size_t &id) {
  if (!this->playerToGame.contains(id)) return;
  std::string gameName = this->playerToGame.at(id);
  this->games.at(gameName)->kick(id);
}

void ServerInGame::move(const InGameOrder &order) {
  if (!this->playerToGame.contains(order.getPlayerId())) return;
  std::string gameName = this->playerToGame.at(order.getPlayerId());
  Coordinate& displacement = this->movements.at(order.getDirection());
  this->games.at(gameName)->move(order.getPlayerId(), displacement);
}

void ServerInGame::attack(const InGameOrder &order) {
  if (!this->playerToGame.contains(order.getPlayerId())) return;
  std::string gameName = this->playerToGame.at(order.getPlayerId());
  this->games.at(gameName)->attack(order.getPlayerId());
}

void ServerInGame::pickUp(const InGameOrder &order) {
  if (!this->playerToGame.contains(order.getPlayerId())) return;
  std::string gameName = this->playerToGame.at(order.getPlayerId());
  this->games.at(gameName)->takeDrop(order.getPlayerId());
}

void ServerInGame::buy(const InGameOrder &order) {
  if (!this->playerToGame.contains(order.getPlayerId())) return;
  std::string gameName = this->playerToGame.at(order.getPlayerId());
  this->games.at(gameName)->buy(order.getPlayerId(), order.getProduct(), order.getAmount());
}

void ServerInGame::changeAngle(const InGameOrder &order) {
  if (!this->playerToGame.contains(order.getPlayerId())) return;
  std::string gameName = this->playerToGame.at(order.getPlayerId());
  this->games.at(gameName)->changeAngle(order.getPlayerId(), order.getAngle());
}

void ServerInGame::changeWeapon(const InGameOrder &order) {
  if (!this->playerToGame.contains(order.getPlayerId())) return;
  std::string gameName = this->playerToGame.at(order.getPlayerId());
  this->games.at(gameName)->setWeapon(order.getPlayerId(), order.getWeaponInformation());
}

void ServerInGame::plantBomb(const InGameOrder &order) {
  if (!this->playerToGame.contains(order.getPlayerId())) return;
  std::string gameName = this->playerToGame.at(order.getPlayerId());
  std::shared_ptr<GameMonitor>& game = this->games.at(gameName);
  game->setWeapon(order.getPlayerId(), 3);
  game->attack(order.getPlayerId());
}

void ServerInGame::defuseBomb(const InGameOrder &order) {
  if (!this->playerToGame.contains(order.getPlayerId())) return;
  std::string gameName = this->playerToGame.at(order.getPlayerId());
  this->games.at(gameName)->deactivateBomb(order.getPlayerId());
}

std::vector<size_t> ServerInGame::getGameIds(std::string gameName) {
    std::vector<size_t> ids;
    for (auto&[id, game]: this->playerToGame) {
        if (gameName == game) {
            ids.emplace_back(id);
        }
    }
    return ids;
}

void ServerInGame::eraseGame(const std::string& gameName) {
    if (!this->games.contains(gameName)) return;
    this->games.at(gameName)->join();
    std::vector<size_t> ids = this->getGameIds(gameName);
    for (auto& id: ids) {
        this->protocol.disconnect({id});
    }
    this->games.erase(gameName);
    std::erase_if(this->playerToGame, [&](const auto& pair) {
        return pair.second == gameName;
    });
}

void ServerInGame::exit(const InGameOrder& order) {
    if (!this->playerToGame.contains(order.getPlayerId()))
        return;
    std::string gameName = this->playerToGame.at(order.getPlayerId());
    this->games.at(gameName)->kick(order.getPlayerId());
    this->playerToGame.erase(order.getPlayerId());
    this->protocol.disconnect({order.getPlayerId()});
}
void ServerInGame::erase() {
    while (true) {
        try {
            std::string gameName = this->gamesToErase.pop();
            this->eraseGame(gameName);
        } catch (ClosedQueue&) {
            break;
        }
    }
}

ServerInGame::~ServerInGame() {
    this->gamesToErase.close();
    this->eraserThread.join();
    for (auto& game: this->games | std::views::values) {
        game->stop();
        game->join();
    }
}
