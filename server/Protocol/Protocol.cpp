#include "Protocol.h"
#include "../common/liberror.h"
#include <sys/socket.h>

#include "ServerLobbyProtocol.h"
#include "Handlers/ClientHandler.h"
#include "Constants/KeyContants.h"
#include "Constants/ProtocolContants.h"


//TODO IMPLEMENTAR LAS INTERFACES *Protocol
Protocol::Protocol(const std::string& port)
    : acceptorSocket(port.c_str()),
      acceptorThread([this]() { this->handleNewConnection(); }),
      lobbyProtocol(this->connectedUsers),
      gameLobbyProtocol(this->connectedUsers),
      inGameProtocol(this->connectedUsers)
{
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

    requestMapper[SHOOT] = [this](const Request& request) {
        return std::make_unique<InGameOrder>(inGameProtocol.handleRequest(request));
    };

    requestMapper[BUY_AMMO] = [this](const Request& request) {
        return std::make_unique<InGameOrder>(inGameProtocol.handleRequest(request));
    };

    requestMapper[BUY_WEAPON] = [this](const Request& request) {
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
            size_t userId = this->connectedUsers.size();

            this->connectedUsers.emplace(userId, std::make_unique<Socket>(std::move(peer)));

            this->clientsHandlers.emplace(
                userId, std::make_unique<ClientHandler>(*this->connectedUsers.at(userId), userId, this->requestsQueue));

            this->clientsHandlers.at(userId)->start();

        } catch (LibError&) {
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
        throw -1; // TODO: Manejar fin de protocolo
    }
}

ServerLobbyOrder Protocol::sendGamesList(const Request& request) {
    return lobbyProtocol.handleRequest(request);
}

ServerLobbyOrder Protocol::join(const Request& request) {
    return lobbyProtocol.handleRequest(request);
}

ServerLobbyOrder Protocol::create(const Request& request) {
    return lobbyProtocol.handleRequest(request);
}

ServerLobbyOrder Protocol::disconnect(const Request& request) {
    return lobbyProtocol.handleRequest(request);
}


GameLobbyOrder Protocol::ready(const Request& request) {
    return gameLobbyProtocol.handleRequest(request);
}

GameLobbyOrder Protocol::exitLobby(const Request& request) {
    return gameLobbyProtocol.handleRequest(request);
}



InGameOrder Protocol::movement(const Request& request) {
    return inGameProtocol.handleRequest(request);
}

InGameOrder Protocol::shoot(const Request& request) {
    return inGameProtocol.handleRequest(request);
}

InGameOrder Protocol::pickUpItem(const Request& request) {
    return inGameProtocol.handleRequest(request);
}

InGameOrder Protocol::dropItem(const Request& request) {
    return inGameProtocol.handleRequest(request);
}

InGameOrder Protocol::buyAmmo(const Request& request) {
    return inGameProtocol.handleRequest(request);
}

InGameOrder Protocol::buyWeapon(const Request& request) {
    return inGameProtocol.handleRequest(request);
}

InGameOrder Protocol::switchWeapon(const Request& request) {
    return inGameProtocol.handleRequest(request);
}

InGameOrder Protocol::plantBomb(const Request& request) {
    return inGameProtocol.handleRequest(request);
}

InGameOrder Protocol::defuseBomb(const Request& request) {
    return inGameProtocol.handleRequest(request);
}

InGameOrder Protocol::exit(const Request& request) {
    return inGameProtocol.handleRequest(request);
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

Protocol::~Protocol() {
    this->end();
}