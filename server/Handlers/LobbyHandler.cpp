#include "LobbyHandler.h"

#include <map>
#include <vector>
#include <stdexcept>
#include "Constants/OpCodesConstans.h"
#include "Constants/KeyContants.h"

LobbyHandler::LobbyHandler(Socket& user, const size_t &userId)
    : userSocket(user), userId(userId), reader(user) {
    requestMapper[OPCODE_CREATE_GAME] = [&]() { return createRequest(); };
    requestMapper[OPCODE_JOIN_GAME] = [&]() { return joinRequest(); };
    requestMapper[OPCODE_LIST_GAMES] = [&]() { return listGamesRequest(); };
    requestMapper[OPCODE_DISCONNECT] = [&]() { return disconnectRequest(); };
}

Request LobbyHandler::handle(const uint8_t opcode) const {
    if (!requestMapper.contains(opcode)) {
        throw std::runtime_error("Opcode de lobby no registrado: " + std::to_string(opcode));
    }
    return requestMapper.at(opcode)();
}

LobbyHandler::~LobbyHandler() = default;

Request LobbyHandler::createRequest() const {
    std::string gameName = reader.stringReader();
    const uint8_t playerCount = reader.u8tReader();
    const uint8_t gameMap = reader.u8tReader();
    const uint8_t roundsCount = reader.u8tReader();

    std::map<std::string, std::vector<char>> message;
    message.emplace(opCodeKey, std::vector<char>(SINGLE_VALUE, OPCODE_CREATE_GAME));
    message.emplace(nameKey, std::vector<char>(gameName.begin(), gameName.end()));
    message.emplace(playerCountKey, std::vector<char>(SINGLE_VALUE, playerCount));
    message.emplace(gameMapKey, std::vector<char>(SINGLE_VALUE, gameMap));
    message.emplace(roundCountKey, std::vector<char>(SINGLE_VALUE, roundsCount));

    return Request(userId, message);
}

Request LobbyHandler::joinRequest() const {
    std::string gameName = reader.stringReader();

    std::map<std::string, std::vector<char>> message;
    message.emplace(opCodeKey, std::vector<char>(SINGLE_VALUE, OPCODE_JOIN_GAME));
    message.emplace(nameKey, std::vector<char>(gameName.begin(), gameName.end()));

    return Request(userId, message);
}

Request LobbyHandler::listGamesRequest() {
    std::map<std::string, std::vector<char>> message;
    message.emplace(opCodeKey, std::vector<char>(SINGLE_VALUE, OPCODE_LIST_GAMES));

    return Request(userId, message);
}

Request LobbyHandler::disconnectRequest() {
    std::map<std::string, std::vector<char>> message;
    message.emplace(opCodeKey, std::vector<char>(SINGLE_VALUE, OPCODE_DISCONNECT));

    return Request(userId, message);
}
