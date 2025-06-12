#include "ServerLobbyProtocol.h"
#include "Constants/ProtocolContants.h"
#include "Constants/KeyContants.h"
#include <sstream>

#include "Sender/Sender.h"


ServerLobbyProtocol::ServerLobbyProtocol()
{
    requestHandlers[ProtocolConstants::GAME_LIST_REQUEST] = [this](const Request& request) { return sendGamesListHandler(request); };
    requestHandlers[ProtocolConstants::JOIN_GAME]         = [this](const Request& request) { return joinHandler(request); };
    requestHandlers[ProtocolConstants::CREATE_GAME]       = [this](const Request& request) { return createHandler(request); };
    requestHandlers[ProtocolConstants::DISCONNECT]        = [this](const Request& request) { return disconnectHandler(request); };
}

ServerLobbyOrder ServerLobbyProtocol::handleRequest(const Request& request) {
    const uint8_t opCode = request.getRequest().at(opCodeKey).front();

    if (!requestHandlers.contains(opCode)) {
        throw -1; //TODO FIX
    }
    return requestHandlers[opCode](request);
}

ServerLobbyOrder ServerLobbyProtocol::sendGamesListHandler(const Request& request) const {
    const size_t clientId = request.getId();
    return ServerLobbyOrder(ProtocolConstants::GAME_LIST_REQUEST, clientId);
}

ServerLobbyOrder ServerLobbyProtocol::joinHandler(const Request& request) {
    const size_t clientId = request.getId();
    const std::map<std::string, std::vector<char>> message = request.getRequest();

    const std::string gameName(message.at(nameKey).data(), message.at(nameKey).size());

    return ServerLobbyOrder(ProtocolConstants::JOIN_GAME, clientId, gameName);
}

ServerLobbyOrder ServerLobbyProtocol::createHandler(const Request& request) {
    const size_t clientId = request.getId();
    const std::map<std::string, std::vector<char>> message = request.getRequest();

    const std::string gameName(message.at(nameKey).data(), message.at(nameKey).size());
    uint8_t gameMap = message.at(gameMapKey).front();
    uint8_t playerCount = message.at(playerCountKey).front();
    uint8_t roundCount = message.at(roundCountKey).front();

    return ServerLobbyOrder(ProtocolConstants::CREATE_GAME, clientId, gameName, gameMap, playerCount, roundCount);
}

ServerLobbyOrder ServerLobbyProtocol::disconnectHandler(const Request& request) {
    const size_t clientId = request.getId();

    // TODO Implementar lógica de desconexión

    return ServerLobbyOrder(ProtocolConstants::DISCONNECT, clientId);
}


void ServerLobbyProtocol::end() {
    // TODO Finalizar cada LobbyHandler
}

