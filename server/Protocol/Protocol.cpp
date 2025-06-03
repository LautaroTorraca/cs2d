#include "Protocol.h"
#include "../common/liberror.h"
#include <sys/socket.h>

#include "Constants/KeyContants.h"
#include "Constants/ProtocolContants.h"
#include "Constants/SnapshotConstants.h"
#include "Handlers/ClientHandler.h"
#include "ServerLobbyProtocol.h"

ProtocolTesting::ProtocolTesting(const std::string &port)
    : acceptorSocket(port.c_str()),
      acceptorThread([this]() { this->handleNewConnection(); }),
      lobbyProtocol(this->connectedUsers),
      gameLobbyProtocol(this->connectedUsers),
      inGameProtocol(this->connectedUsers),
      handledUsers(0) {
  setupLobbyHandlers();
  setupGameLobbyHandlers();
  setupInGameHandlers();
}

void ProtocolTesting::setupLobbyHandlers() {
  using namespace ProtocolConstants;

  requestMapper[GAME_LIST_REQUEST] = [this](const Request &request) {
    return std::make_unique<ServerLobbyOrder>(
        lobbyProtocol.handleRequest(request));
  };

  requestMapper[JOIN_GAME] = [this](const Request &request) {
    return std::make_unique<ServerLobbyOrder>(
        lobbyProtocol.handleRequest(request));
  };

  requestMapper[CREATE_GAME] = [this](const Request &request) {
    return std::make_unique<ServerLobbyOrder>(
        lobbyProtocol.handleRequest(request));
  };

  requestMapper[LOBBY_DISCONNECT] = [this](const Request &request) {
    return std::make_unique<ServerLobbyOrder>(
        lobbyProtocol.handleRequest(request));
  };
}

void ProtocolTesting::setupGameLobbyHandlers() {
  using namespace ProtocolConstants;

  requestMapper[READY] = [this](const Request &request) {
    return std::make_unique<GameLobbyOrder>(
        gameLobbyProtocol.handleRequest(request));
  };

  requestMapper[EXIT_LOBBY] = [this](const Request &request) {
    return std::make_unique<GameLobbyOrder>(
        gameLobbyProtocol.handleRequest(request));
  };
}

void ProtocolTesting::setupInGameHandlers() {
  using namespace ProtocolConstants;

  requestMapper[PLAYER_MOVEMENT] = [this](const Request &request) {
    return std::make_unique<InGameOrder>(inGameProtocol.handleRequest(request));
  };

  requestMapper[EXIT_GAME] = [this](const Request &request) {
    return std::make_unique<InGameOrder>(inGameProtocol.handleRequest(request));
  };

  requestMapper[SHOOT] = [this](const Request &request) {
    return std::make_unique<InGameOrder>(inGameProtocol.handleRequest(request));
  };

  requestMapper[BUY_AMMO] = [this](const Request &request) {
    return std::make_unique<InGameOrder>(inGameProtocol.handleRequest(request));
  };

  requestMapper[BUY_WEAPON] = [this](const Request &request) {
    return std::make_unique<InGameOrder>(inGameProtocol.handleRequest(request));
  };

  requestMapper[PICK_UP_ITEM] = [this](const Request &request) {
    return std::make_unique<InGameOrder>(inGameProtocol.handleRequest(request));
  };

  requestMapper[DROP_ITEM] = [this](const Request &request) {
    return std::make_unique<InGameOrder>(inGameProtocol.handleRequest(request));
  };

  requestMapper[SWITCH_WEAPON] = [this](const Request &request) {
    return std::make_unique<InGameOrder>(inGameProtocol.handleRequest(request));
  };

  requestMapper[PLANT_BOMB] = [this](const Request &request) {
    return std::make_unique<InGameOrder>(inGameProtocol.handleRequest(request));
  };

  requestMapper[DEFUSE_BOMB] = [this](const Request &request) {
    return std::make_unique<InGameOrder>(inGameProtocol.handleRequest(request));
  };
}

void ProtocolTesting::handleNewConnection() {
  while (true) {
    try {
      Socket peer = this->acceptorSocket.accept();
      size_t userId = handledUsers++;

      this->connectedUsers.emplace(userId,
                                   std::make_unique<Socket>(std::move(peer)));

      this->clientsHandlers.emplace(
          userId,
          std::make_unique<ClientHandler>(*this->connectedUsers.at(userId),
                                          userId, this->requestsQueue));

      this->clientsHandlers.at(userId)->start();

    } catch (LibError &) {
      break;
    }
  }
}

std::unique_ptr<Order> ProtocolTesting::getNextOrder() {
  try {
    const Request request = std::move(*this->requestsQueue.pop());
    const uint8_t code = request.getRequest().at(opCodeKey).front();
    return this->requestMapper.at(code)(request);
  } catch (ClosedQueue &) {
    throw -1; // TODO: Manejar fin de protocolo
  }
}

ServerLobbyOrder ProtocolTesting::sendGamesList(const Request &request) {
  return lobbyProtocol.handleRequest(request);
}

ServerLobbyOrder ProtocolTesting::join(const Request &request) {
  return lobbyProtocol.handleRequest(request);
}

ServerLobbyOrder ProtocolTesting::create(const Request &request) {
  return lobbyProtocol.handleRequest(request);
}

ServerLobbyOrder ProtocolTesting::disconnect(const Request &request) {
  return lobbyProtocol.handleRequest(request);
}

GameLobbyOrder ProtocolTesting::ready(const Request &request) {
  return gameLobbyProtocol.handleRequest(request);
}

GameLobbyOrder ProtocolTesting::exitLobby(const Request &request) {
  return gameLobbyProtocol.handleRequest(request);
}

InGameOrder ProtocolTesting::movement(const Request &request) {
  return inGameProtocol.handleRequest(request);
}

InGameOrder ProtocolTesting::shoot(const Request &request) {
  return inGameProtocol.handleRequest(request);
}

InGameOrder ProtocolTesting::pickUpItem(const Request &request) {
  return inGameProtocol.handleRequest(request);
}

InGameOrder ProtocolTesting::dropItem(const Request &request) {
  return inGameProtocol.handleRequest(request);
}

InGameOrder ProtocolTesting::buyAmmo(const Request &request) {
  return inGameProtocol.handleRequest(request);
}

InGameOrder ProtocolTesting::buyWeapon(const Request &request) {
  return inGameProtocol.handleRequest(request);
}

InGameOrder ProtocolTesting::switchWeapon(const Request &request) {
  return inGameProtocol.handleRequest(request);
}

InGameOrder ProtocolTesting::plantBomb(const Request &request) {
  return inGameProtocol.handleRequest(request);
}

InGameOrder ProtocolTesting::defuseBomb(const Request &request) {
  return inGameProtocol.handleRequest(request);
}

InGameOrder ProtocolTesting::exit(const Request &request) {
  return inGameProtocol.handleRequest(request);
}

<<<<<<< HEAD
// TODO ARREGLAR EN COMO *** VAMOS A MANDAR LA SNAPSHOT
void ProtocolTesting::sendSnapshot(const Snapshot &snapshot,
                                   const size_t &userId) {
  this->clientsHandlers.at(userId)->sendSnapshot(snapshot);
}

void ProtocolTesting::sendPreSnapshot(const PreSnapshot &preSnapshot,
                                      const size_t &userId) {
  this->clientsHandlers.at(userId)->sendPreSnapshot(preSnapshot);
=======
void Protocol::sendPreSnapshot(const PreSnapshot &preSnapshot) {
  this->clientsHandlers.at(preSnapshot.clientId)->sendPreSnapshot(preSnapshot);
>>>>>>> 80705a0 (Agregando CMakeList del server configurado y solucionando errores de compilacion del server)
}

void ProtocolTesting::end() {
  try {
    this->acceptorSocket.shutdown(SHUT_RDWR);
    this->acceptorThread.join();
    this->requestsQueue.close();
    for (auto &client : this->clientsHandlers) {
      client.second->stop();
      client.second->join();
    }

  } catch (LibError &) {
    // TODO: Logging de error
  }
}

ProtocolTesting::~ProtocolTesting() { this->end(); }
