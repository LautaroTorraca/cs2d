#include "ServerLobby.h"

#include "Constants/ConnectionStatus.h"
#include "DTO/LobbyConnectionDTO.h"
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
    throw std::runtime_error("The order is not implemented."); // TODO FIX
  }

  translator.at(type)(lobbyOrder);
}

void ServerLobby::createGame(const ServerLobbyOrder &order) {
  try {
    GameLobby gameLobby = this->lobby.createGameLobby(order.getClientId(), order.getGameName(),
                                                        order.getMapType(), order.getRoundCount());
      this->gameLobbyserver.add(order.getGameName(), gameLobby);
      this->lobby.joinGame(order.getClientId(), order.getGameName());
      this->gameLobbyserver.join(order.getGameName(), order.getClientId());
    LobbyConnectionDTO lobbyConnection(order.getClientId(), ConnectionStatus::SUCCESS);
    protocol.sendLobbyConnectionStatus(lobbyConnection);
  }catch (std::runtime_error &e) {
    LobbyConnectionDTO lobbyConnection(order.getClientId(), ConnectionStatus::FAILED);
    protocol.sendLobbyConnectionStatus(lobbyConnection);
  }
}

void ServerLobby::joinGame(const ServerLobbyOrder &order) {
  try {
    this->lobby.joinGame(order.getClientId(), order.getGameName());
    this->gameLobbyserver.join(order.getGameName(), order.getClientId());
    LobbyConnectionDTO lobbyConnection(order.getClientId(), ConnectionStatus::SUCCESS);
    this->protocol.sendLobbyConnectionStatus(lobbyConnection);
  } catch (std::runtime_error &e) {
    LobbyConnectionDTO lobbyConnection(order.getClientId(), ConnectionStatus::FAILED);
    this->protocol.sendLobbyConnectionStatus(lobbyConnection);
  }
}

void ServerLobby::leaveGame(const ServerLobbyOrder &order) const {
  DisconnectionDTO disconnectionInfo(order.getClientId());
  this->protocol.disconnect(disconnectionInfo);
}

void ServerLobby::listGames(const ServerLobbyOrder &order) const {
  size_t id = order.getClientId();
  GamesListDTO gamesList = this->gameLobbyserver.listLobbies(id);

  this->protocol.sendGamesList(gamesList);
}
