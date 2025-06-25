#include "Protocol.h"

#include <iostream>
#include <ranges>

#include <sys/socket.h>

#include "common/Constants/SnapshotConstants.h"
#include "common/Constants/ProtocolContants.h"
#include "common/liberror.h"
#include "server/Constants/KeyContants.h"

#include "ServerLobbyProtocol.h"

Protocol::Protocol(const std::string& port):
        acceptorSocket(port.c_str()),
        acceptorThread([this]() { this->handleNewConnection(); }),
        handledUsers(0),
        ended(false) {
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
            this->clientsHandlers.emplace(
                    userId, std::make_unique<ClientHandler>(peer,
                                                            userId,
                                                            this->requestsQueue));
            this->clientsHandlers.at(userId)->start();
        } catch (LibError& e) {
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
        throw;
    }
}

void Protocol::sendGamesList(GamesListDTO& gamesList) {
    this->clientsHandlers.at(gamesList.id)->sendGamesList(gamesList);
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
        if ( this->clientsHandlers.contains(playerInfo.getId()))
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

void Protocol::sendSnapshot(const GameInfoDTO& gameInfo, const size_t& id) {
    this->clientsHandlers.at(id)->sendSnapshot(gameInfo);
}

void Protocol::sendPreSnapshot(const PreSnapshot& preSnapshot) {
    this->clientsHandlers.at(preSnapshot.clientId)->sendPreSnapshot(preSnapshot);
}

void Protocol::end() {
    if (this->ended) return;
    try {
        this->acceptorSocket.shutdown(SHUT_RDWR);
        this->acceptorThread.join();
        for (auto& handler: this->clientsHandlers | std::views::values) {
            handler->endService();
            handler->join();
        }
        this->clientsHandlers.clear();
        this->requestsQueue.close();
        this->ended = true;

    } catch (LibError&) {
        //Logg: Error de coneccion
    }
}

Protocol::~Protocol() { this->end(); }
