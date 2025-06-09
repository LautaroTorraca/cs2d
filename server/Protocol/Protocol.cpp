#include "Protocol.h"

#include <iostream>

#include <sys/socket.h>

#include "Constants/KeyContants.h"
#include "Constants/ProtocolContants.h"
#include "Constants/SnapshotConstants.h"
#include "Handlers/ClientHandler.h"
#include "common/liberror.h"

#include "ServerLobbyProtocol.h"

Protocol::Protocol(const std::string& port):
        acceptorSocket(port.c_str()),
        acceptorThread([this]() { this->handleNewConnection(); }),
        lobbyProtocol(this->connectedUsers),
        gameLobbyProtocol(this->connectedUsers),
        inGameProtocol(this->connectedUsers),
        handledUsers(0) {
    setupLobbyHandlers();
    setupGameLobbyHandlers();
    setupInGameHandlers();
}

void Protocol::setupLobbyHandlers() {
    using namespace ProtocolConstants;

    requestMapper[GAME_LIST_REQUEST] = [this](const Request& request) {
        return std::make_unique<ServerLobbyOrder>(lobbyProtocol.handleRequest(request));
    };

    requestMapper[JOIN_GAME] = [this](const Request& request) {
        return std::make_unique<ServerLobbyOrder>(lobbyProtocol.handleRequest(request));
    };

    requestMapper[CREATE_GAME] = [this](const Request& request) {
        return std::make_unique<ServerLobbyOrder>(lobbyProtocol.handleRequest(request));
    };

    requestMapper[LOBBY_DISCONNECT] = [this](const Request& request) {
        return std::make_unique<ServerLobbyOrder>(lobbyProtocol.handleRequest(request));
    };
}

void Protocol::setupGameLobbyHandlers() {
    using namespace ProtocolConstants;

    requestMapper[READY] = [this](const Request& request) {
        return std::make_unique<GameLobbyOrder>(gameLobbyProtocol.handleRequest(request));
    };

    requestMapper[EXIT_LOBBY] = [this](const Request& request) {
        return std::make_unique<GameLobbyOrder>(gameLobbyProtocol.handleRequest(request));
    };
}

void Protocol::setupInGameHandlers() {
    using namespace ProtocolConstants;

    requestMapper[PLAYER_MOVEMENT] = [this](const Request& request) {
        return std::make_unique<InGameOrder>(inGameProtocol.handleRequest(request));
    };

    requestMapper[EXIT_GAME] = [this](const Request& request) {
        return std::make_unique<InGameOrder>(inGameProtocol.handleRequest(request));
    };

    requestMapper[ATTACK] = [this](const Request& request) {
        return std::make_unique<InGameOrder>(inGameProtocol.handleRequest(request));
    };

    requestMapper[BUY] = [this](const Request& request) {
        return std::make_unique<InGameOrder>(inGameProtocol.handleRequest(request));
    };

    requestMapper[CHANGE_ANGLE] = [this](const Request& request) {
        return std::make_unique<InGameOrder>(inGameProtocol.handleRequest(request));
    };

    requestMapper[PICK_UP_ITEM] = [this](const Request& request) {
        return std::make_unique<InGameOrder>(inGameProtocol.handleRequest(request));
    };

    requestMapper[DROP_ITEM] = [this](const Request& request) {
        return std::make_unique<InGameOrder>(inGameProtocol.handleRequest(request));
    };

    requestMapper[SWITCH_WEAPON] = [this](const Request& request) {
        return std::make_unique<InGameOrder>(inGameProtocol.handleRequest(request));
    };

    requestMapper[PLANT_BOMB] = [this](const Request& request) {
        return std::make_unique<InGameOrder>(inGameProtocol.handleRequest(request));
    };

    requestMapper[DEFUSE_BOMB] = [this](const Request& request) {
        return std::make_unique<InGameOrder>(inGameProtocol.handleRequest(request));
    };
}

void Protocol::handleNewConnection() {
    while (true) {
        try {
            Socket peer = this->acceptorSocket.accept();
            size_t userId = handledUsers++;

            this->connectedUsers.emplace(userId, std::make_unique<Socket>(std::move(peer)));

            this->clientsHandlers.emplace(
                    userId, std::make_unique<ClientHandler>(*this->connectedUsers.at(userId),
                                                            userId, this->requestsQueue));

            this->clientsHandlers.at(userId)->start();
            std::cout << "creo todo bien (el socket)\n";
        } catch (LibError&) {
            std::cout << "ERROR GARRAFAL";
            break;
        }
    }
}

std::unique_ptr<Order> Protocol::getNextOrder() {
    try {
        const Request request = std::move(*this->requestsQueue.pop());
        const uint8_t code = request.getRequest().at(opCodeKey).front();
        return this->requestMapper.at(code)(request);
    } catch (ClosedQueue&) {
        throw -1;  // TODO: Manejar fin de protocolo
    }
}

void Protocol::sendGamesList(GamesListDTO& gamesList) {
    this->clientsHandlers.at(gamesList.id)->sendGamesList(gamesList.games);
}

void Protocol::sendLobbyConnectionStatus(const LobbyConnectionDTO& lobbyConnection) {
    this->clientsHandlers.at(lobbyConnection.id)->sendLobbyConnectonStatus(lobbyConnection);
}

void Protocol::disconnect(const DisconnectionDTO &disconnectionInfo) {
  if (!this->clientsHandlers.contains(disconnectionInfo.clientId)) return;
  std::unique_ptr<ClientHandler>& client = this->clientsHandlers.at(disconnectionInfo.clientId);
  client->stopService();
  client->join();
  this->clientsHandlers.erase(disconnectionInfo.clientId);
}

std::vector<size_t> Protocol::getIds(const GameLobbyDTO& gameLobbyInfo) {
    std::vector<PlayerChoicesDTO> playersChoices = gameLobbyInfo.playersChoices;
    std::vector<size_t> ids;
    for (auto& playerChoices: playersChoices) {
        ids.emplace_back(playerChoices.id);
    }
    return ids;
}

void Protocol::sendLobby(const GameLobbyDTO& gameLobbyInfo) {
    std::vector<size_t> ids = getIds(gameLobbyInfo);
    for (auto& id: ids) {
        this->clientsHandlers.at(id)->sendGameLobby(gameLobbyInfo);
    }
}

std::vector<size_t> Protocol::getSnapshotIds(const std::vector<PlayerInfoDTO>& playerInfos) {
    std::vector<size_t> snapshotIds;
    for (auto& playerInfo: playerInfos) {
        snapshotIds.emplace_back(playerInfo.getId());
    }
    return snapshotIds;
}

void Protocol::sendSnapshot(const GameInfoDTO& gameInfo) {
    std::vector<size_t> playersIds = this->getSnapshotIds(gameInfo.getPlayersInfo());
    for (auto& playerId: playersIds) {
        this->clientsHandlers.at(playerId)->sendSnapshot(gameInfo);
    }
}

void Protocol::sendPreSnapshot(const PreSnapshot& preSnapshot) {
    this->clientsHandlers.at(preSnapshot.clientId)->sendPreSnapshot(preSnapshot);
}

void Protocol::end() {
    try {
        this->acceptorSocket.shutdown(SHUT_RDWR);
        this->acceptorThread.join();
        this->requestsQueue.close();
        for (auto& client: this->clientsHandlers) {
            client.second->stop();
            client.second->join();
        }

    } catch (LibError&) {
        // TODO: Logging de error
    }
}

Protocol::~Protocol() { this->end(); }
