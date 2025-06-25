#include "ServerGameLobby.h"

#include <ranges>

#include "GameLogic/Exceptions/GameAlreadyExistsException.h"
#include "GameLogic/Exceptions/OrderNotImplementedException.h"
#include "Interfaces/GameLobbyProtocolInterface.h"

ServerGameLobby::ServerGameLobby(ServerInGame& serverInGame, GameLobbyProtocolInterface& protocol, const std::function<void(const size_t&)>& eraser) : serverInGame(serverInGame), protocol(protocol), eraser(eraser) { setupTranslators(); }

void ServerGameLobby::setupTranslators() {
  translator[GAME_LOBBY_READY] = [&](const GameLobbyOrder &order) { this->ready(order); };

  translator[GAME_LOBBY_EXIT] = [&](const GameLobbyOrder &order) { this->exit(order); };
}

void ServerGameLobby::handle(const std::unique_ptr<Order> &order) const {
  GameLobbyOrder &gameLobbyOrder = dynamic_cast<GameLobbyOrder &>(*order);
  OrderType type = gameLobbyOrder.getOrderType();


  if (!translator.contains(type)) {
    throw OrderNotImplementedException("The requested action is not implemented.");
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

void ServerGameLobby::deleteAndCreate(GameLobbyDTO &gameLobbyInfo) {
    if (gameLobbyInfo.status != READY_STATUS) return;
    std::erase_if(this->playersToLobby,
                  [&](const auto& pair) { return pair.second == gameLobbyInfo.gameName; });
    this->gameLobbies.erase(gameLobbyInfo.gameName);
    this->serverInGame.addNewGame(gameLobbyInfo.gameName, gameLobbyInfo);
    for (const auto& player :gameLobbyInfo.playersChoices) {
        this->eraser(player.id);
    }
}

void ServerGameLobby::exit(const GameLobbyOrder& order) {
    std::string gameName = this->playersToLobby.at(order.getPlayerId());
    GameLobby& gameLobby = this->gameLobbies.at(gameName);
    gameLobby.kick(order.getPlayerId());
    this->playersToLobby.erase(order.getPlayerId());
    this->eraser(order.getPlayerId());
    GameLobbyDTO gameLobbyInfo = gameLobby.getInfo();
    if (gameLobbyInfo.status == INVALID_STATUS) {
        this->gameLobbies.erase(gameName);
    }
    this->deleteAndCreate(gameLobbyInfo);
}

GamesListDTO ServerGameLobby::listLobbies(const size_t& id) {
  std::vector<GameLobbyDTO> gameLobbies;
  for ( auto& [gameName,gameLobby] : this->gameLobbies) {
      gameLobbies.emplace_back(gameLobby.getInfo());
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
  this->deleteAndCreate(gameLobbyInfo);
}
