#include "ServerGameLobby.h"

#include <ranges>

#include "Interfaces/GameLobbyProtocolInterface.h"

ServerGameLobby::ServerGameLobby(ServerInGame& serverInGame, GameLobbyProtocolInterface& protocol) : serverInGame(serverInGame), protocol(protocol) { setupTranslators(); }

void ServerGameLobby::setupTranslators() {
  translator[GAME_LOBBY_READY] = [&](const GameLobbyOrder &order) { this->ready(order); };

  translator[GAME_LOBBY_EXIT] = [&](const GameLobbyOrder &order) { this->exit(order); };
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
  GameLobby& gameLobby = this->gameLobbies.at(gameName);
  gameLobby.join(playerId);
  GameLobbyDTO gameLobbyInfo = gameLobby.getInfo();
  this->protocol.sendLobby(gameLobbyInfo);
}

void ServerGameLobby::exit(const GameLobbyOrder &order) {
  std::string gameName = this->playersToLobby.at(order.getPlayerId());
  GameLobby& gameLobby = this->gameLobbies.at(gameName);
  gameLobby.kick(order.getPlayerId());
  this->protocol.disconnect({ order.getPlayerId() });
  GameLobbyDTO gameLobbyInfo = gameLobby.getInfo();
  if (gameLobbyInfo.status == READY_STATUS) {
    this->serverInGame.addNewGame(gameName, gameLobbyInfo);
  }
}

GamesListDTO ServerGameLobby::listLobbies(const size_t& id) {
  std::vector<GameLobbyDTO> gameLobbies;
  for ( auto& [gameName,gameLobby] : this->gameLobbies) {
    if (gameLobby.getInfo().status != READY_STATUS) {
      gameLobbies.emplace_back(gameLobby.getInfo());
    }
  }
  return {id, gameLobbies};
}

void ServerGameLobby::ready(const GameLobbyOrder &order) {
  if (!this->playersToLobby.contains(order.getPlayerId())) return;
  std::string gameName = this->playersToLobby.at(order.getPlayerId());
  GameLobby& gameLobby = this->gameLobbies.at(gameName);
  gameLobby.select(order.getPlayerId(), order.getPlayerName(), order.getTeamId(), order.getSkinId());
  GameLobbyDTO gameLobbyInfo = gameLobby.getInfo();
  this->protocol.sendLobby(gameLobbyInfo);
  if (gameLobbyInfo.status == GameLobbyStatus::READY_STATUS) {
    this->serverInGame.addNewGame(gameName, gameLobbyInfo);
    this->gameLobbies.erase(gameName);
      this->playersToLobby.erase(order.getPlayerId());
  }
}
