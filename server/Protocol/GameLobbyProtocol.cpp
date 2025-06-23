#include "GameLobbyProtocol.h"

#include "server/Constants/KeyContants.h"
#include "server/Constants/ProtocolContants.h"
#include "server/OrderNotImplementedException.h"


GameLobbyProtocol::GameLobbyProtocol() {
    requestHandlers[ProtocolConstants::READY]       = [this](const Request& request) { return readyHandler(request); };
    requestHandlers[ProtocolConstants::EXIT_LOBBY]  = [this](const Request& request) { return exitLobbyHandler(request); };
}


GameLobbyOrder GameLobbyProtocol::handleRequest(const Request& request) {
    const uint8_t opCode = request.getRequest().at(opCodeKey).front();

    if (!requestHandlers.contains(opCode)) {
        throw OrderNotImplementedException("The GameLobby Order is not implemented.");
    }
    return requestHandlers[opCode](request);
}


GameLobbyOrder GameLobbyProtocol::readyHandler(const Request& request) {
    const size_t clientId = request.getId();
    const std::map<std::string, std::vector<char>> message = request.getRequest();
    const std::string playerName(message.at(playerNameKey).data(), message.at(playerNameKey).size());
    const uint8_t teamId = message.at(teamKey).front();
    const uint8_t skinId = message.at(skinKey).front();

    return GameLobbyOrder(ProtocolConstants::READY, clientId, playerName, teamId, skinId);
}

GameLobbyOrder GameLobbyProtocol::exitLobbyHandler(const Request& request) {
    const size_t clientId = request.getId();
    return GameLobbyOrder(ProtocolConstants::EXIT_LOBBY, clientId);
}

void GameLobbyProtocol::registerClient(size_t clientId, std::unique_ptr<GameLobbyHandler> handler) {
    lobbyUsers.emplace(clientId, std::move(handler));
}

void GameLobbyProtocol::end() {
    lobbyUsers.clear();
}
