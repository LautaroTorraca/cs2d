#include "ServerLobby.h"

#include "Constants/ConnectionStatus.h"
#include "DTO/LobbyConnectionDTO.h"
#include "server/ServerGameLobby.h"

#include "OrderNotImplementedException.h"

#define DEFAULT_CONNECTION_MESSAGE "Good."

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
    throw OrderNotImplementedException("The order is not implemented.");
  }

  translator.at(type)(lobbyOrder);
}

void ServerLobby::createGame(const ServerLobbyOrder &order) {
  try {
    GameLobby gameLobby = this->lobby.createGameLobby(order.getClientId(), order.getGameName(),
                                                        order.getMapType(), order.getRoundCount(), order.getPlayerCount());
      this->gameLobbyserver.add(order.getGameName(), gameLobby);
      this->gameLobbyserver.join(order.getGameName(), order.getClientId());
      const LobbyConnectionDTO lobbyConnection(order.getClientId(), ConnectionStatus::SUCCESS, DEFAULT_CONNECTION_MESSAGE);
    protocol.sendLobbyConnectionStatus(lobbyConnection);
  }catch (std::exception &e) {
      const LobbyConnectionDTO lobbyConnection(order.getClientId(), ConnectionStatus::FAILED, e.what());
    protocol.sendLobbyConnectionStatus(lobbyConnection);
  }
}

void ServerLobby::joinGame(const ServerLobbyOrder &order) {
  try {
    this->lobby.joinGame(order.getClientId(), order.getGameName());
    this->gameLobbyserver.join(order.getGameName(), order.getClientId());
    LobbyConnectionDTO lobbyConnection(order.getClientId(), ConnectionStatus::SUCCESS, DEFAULT_CONNECTION_MESSAGE);
    this->protocol.sendLobbyConnectionStatus(lobbyConnection);
  } catch (std::invalid_argument &e) {
    LobbyConnectionDTO lobbyConnection(order.getClientId(), ConnectionStatus::FAILED, e.what());
    this->protocol.sendLobbyConnectionStatus(lobbyConnection);
  }
}

void ServerLobby::leaveGame(const ServerLobbyOrder &order) {
    DisconnectionDTO disconnectionInfo(order.getClientId());
    this->lobby.erase(order.getClientId());
    this->protocol.disconnect(disconnectionInfo);
}

void ServerLobby::listGames(const ServerLobbyOrder& order) const {
    size_t id = order.getClientId();
    GamesListDTO gamesList = this->gameLobbyserver.listLobbies(id);

    this->protocol.sendGamesList(gamesList);
}
void ServerLobby::erase(const size_t& id) {
    this->lobby.erase(id);
}
