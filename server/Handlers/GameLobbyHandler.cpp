#include "GameLobbyHandler.h"

#include <map>
#include <vector>
#include <stdexcept>
#include "server/Constants/OpCodesConstans.h"
#include "server/Constants/KeyContants.h"

GameLobbyHandler::GameLobbyHandler(Socket& user, const size_t &userId) : userSocket(user), userId(userId), reader(user) {
    requestMapper[OPCODE_READY] = [&]() { return readyRequest(); };
    requestMapper[OPCODE_EXIT_LOBBY] = [&]() { return exitGameLobbyRequest(); };
}

Request GameLobbyHandler::handle(const uint8_t opcode) const {
    if (!requestMapper.contains(opcode)) {
        throw std::runtime_error("Opcode de GameLobby no registrado: " + std::to_string(opcode));
    }
    return requestMapper.at(opcode)();
}


Request GameLobbyHandler::readyRequest() const {
    std::map<std::string, std::vector<char>> message;
    std::string playerName = this->reader.stringReader();
    uint8_t team = this->reader.u8tReader();
    uint8_t skin = this->reader.u8tReader();
    message.emplace(opCodeKey, std::vector<char>(SINGLE_VALUE, OPCODE_READY));
    message.emplace(playerNameKey, std::vector<char>(playerName.begin(), playerName.end()));
    std::vector<char> teamData;
    teamData.emplace_back(team);
    message.emplace(teamKey, teamData);
    std::vector<char> skinData;
    skinData.emplace_back(skin);
    message.emplace(skinKey, skinData);
    return Request(userId, message);
}

Request GameLobbyHandler::exitGameLobbyRequest() const {
    std::map<std::string, std::vector<char>> message;
    message.emplace(opCodeKey, std::vector<char>(SINGLE_VALUE, OPCODE_EXIT_LOBBY));

    return Request(userId, message);
}

GameLobbyHandler::~GameLobbyHandler() = default;
