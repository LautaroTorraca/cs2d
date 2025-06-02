#include "ServerGameLobby.h"

ServerGameLobby::ServerGameLobby(ServerInGame& serverInGame) : serverInGame(serverInGame) { setupTranslators(); }

void ServerGameLobby::setupTranslators() {
  translator[GAME_LOBBY_READY] = [&](const GameLobbyOrder &order) {this->ready(order);};

  translator[GAME_LOBBY_EXIT] = [](const GameLobbyOrder &) {};
}

void ServerGameLobby::handle(const std::unique_ptr<Order> &order) const {
  GameLobbyOrder &gameLobbyOrder = dynamic_cast<GameLobbyOrder &>(*order);
  OrderType type = gameLobbyOrder.getOrderType();

  if (!translator.contains(type)) {
    throw -1; // TODO FIX
  }

  translator.at(type)(gameLobbyOrder);
}

void ServerGameLobby::add(const std::string &gameName, GameLobby &gameLobby) {
  if (this->gameLobbies.contains(gameName)) return;
  this->gameLobbies.emplace(gameName, std::move(gameLobby));
}

void ServerGameLobby::join(const std::string &gameName, const size_t &playerId) {
  if (this->playersToLobby.contains(playerId) || !this->gameLobbies.contains(gameName)) return;
  this->playersToLobby.emplace(playerId, gameName);
  this->gameLobbies.at(gameName).join(playerId);
}

void ServerGameLobby::ready(const GameLobbyOrder &order) {
  if (!this->playersToLobby.contains(order.getPlayerId())) return;
  std::string gameName = this->playersToLobby.at(order.getPlayerId());
  GameLobby& gameLobby = this->gameLobbies.at(gameName);
  gameLobby.select(order.getPlayerId(), order.getPlayerName(), order.getTeamId(), order.getSkinId());
  GameLobbyDTO gameLobbyInfo = gameLobby.getInfo();
  if (gameLobbyInfo.status == GameLobbyStatus::READY_STATUS) {
    this->serverInGame.addNewGame(gameName, gameLobbyInfo);
  }
}
