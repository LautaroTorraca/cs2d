#include "ServerLobby.h"

#include "ServerGameLobby.h"

ServerLobby::ServerLobby(ServerLobbyProtocolInterface& protocol, ServerGameLobby& serverGameLobby) :
protocol(protocol), gameLobbyserver(serverGameLobby) { setupTranslators(); }

void ServerLobby::setupTranslators() {
  translator[LOBBY_CREATE] = [&](const ServerLobbyOrder &order) { this->createGame(order); };

  translator[LOBBY_LIST] = [&](const ServerLobbyOrder &order) { this->listGames(order); };

  translator[LOBBY_JOIN] = [&](const ServerLobbyOrder &order) { this->joinGame(order); };

  translator[LOBBY_DISCONNECT] = [&](const ServerLobbyOrder &order) { this->leaveGame(order); };
}

void ServerLobby::handle(const std::unique_ptr<Order> &order) const {
  ServerLobbyOrder &lobbyOrder = dynamic_cast<ServerLobbyOrder &>(*order);
  const OrderType type = lobbyOrder.getOrderType();

  if (!translator.contains(type)) {
    throw -1; // TODO FIX
  }

  translator.at(type)(lobbyOrder);
}

void ServerLobby::createGame(const ServerLobbyOrder &order) {
  GameLobby gameLobby = this->lobby.createGameLobby(order.getClientId(), order.getGameName(), order.getMapType(), order.getRoundCount());
  this->gameLobbyserver.add(order.getGameName(), gameLobby);
  this->joinGame(order);
}

void ServerLobby::listGames(const ServerLobbyOrder& order) const {
  std::vector<std::string> games = this->lobby.listGames();
  GamesListDTO gamesList(order.getClientId(), games);
  protocol.sendGamesList(gamesList);
}

void ServerLobby::joinGame(const ServerLobbyOrder &order) const {
  this->gameLobbyserver.join(order.getGameName(), order.getClientId());
}

void ServerLobby::leaveGame(const ServerLobbyOrder &order) const {
  DisconnectionDTO disconnectionInfo(order.getClientId());
  this->protocol.disconnect(disconnectionInfo);
}
