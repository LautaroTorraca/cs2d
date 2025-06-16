#include "Protocol.h"

#include <iostream>
#include <sstream>
#include <string>

// #include "server/Constants/OpCodesConstans.h"
#include "server/Constants/ProtocolContants.h"

#define NEW 0X6E
Protocol::Protocol(const std::string& hostName, const std::string& port):
        clientSocket(hostName.c_str(), port.c_str()), sender(clientSocket), reader(clientSocket) {}

void Protocol::createLobby(const LobbyDTO& lobbyInfo) {
    uint8_t code = ProtocolConstants::CREATE_GAME;
    uint8_t mapType = static_cast<uint8_t>(lobbyInfo.mapType);
    this->sender.send(code);
    this->sender.send(lobbyInfo.gameName);
    this->sender.send(lobbyInfo.playersCount);
    this->sender.send(mapType);
    this->sender.send(lobbyInfo.rounds);
}

LobbyConnectionDTO Protocol::getLobbyConnection() const {
    size_t id = this->reader.readSizeT();
    ConnectionStatus status = static_cast<ConnectionStatus>(this->reader.u8tReader());
    return LobbyConnectionDTO(id, status);
}

GamesList Protocol::getGamesList() {
    uint8_t code = ProtocolConstants::GAME_LIST_REQUEST;
    this->sender.send(code);
    std::string games = this->reader.stringReader();
    std::stringstream ss(games);
    std::vector<std::string> gotGames;
    std::string game;

    while (ss >> game) {
        gotGames.push_back(game);
    }

    return {gotGames};
}

void Protocol::joinLobby(const LobbyDTO& lobbyInfo) {
    uint8_t code = ProtocolConstants::JOIN_GAME;
    this->sender.send(code);
    this->sender.send(lobbyInfo.gameName);
}

void Protocol::leaveLobby() {
    uint8_t code = ProtocolConstants::DISCONNECT;
    this->sender.send(code);
}

void Protocol::ready(const PlayerChoicesDTO& playerChoices) {
    uint8_t code = ProtocolConstants::READY;
    uint8_t team = static_cast<uint8_t>(playerChoices.team);
    uint8_t skin = static_cast<uint8_t>(playerChoices.skin);
    this->sender.send(code);
    this->sender.send(playerChoices.playerName);
    this->sender.send(team);
    this->sender.send(skin);
}

GameLobbyDTO Protocol::getGameLobby() const {
    GameLobbyStatus status = static_cast<GameLobbyStatus>(this->reader.u8tReader());
    std::vector<PlayerChoicesDTO> choices;
    while (this->reader.u8tReader() == NEW) {
        choices.push_back(this->readPlayerChoices());
    }
    std::string gamaName = this->reader.stringReader();
    uint8_t rounds = this->reader.u8tReader();
    MapType mapType = static_cast<MapType>(this->reader.u8tReader());
    return GameLobbyDTO(status, choices, gamaName, rounds, mapType);
}

void Protocol::leaveGameLobby() {
    uint8_t code = ProtocolConstants::EXIT_LOBBY;
    this->sender.send(code);
}

void Protocol::move(const Direction& direction) {
    const uint8_t opCode = ProtocolConstants::PLAYER_MOVEMENT;
    uint16_t directionMove = direction;
    this->sender.send(opCode);
    this->sender.send(directionMove);
}

void Protocol::attack() {
    const uint8_t opCode = ProtocolConstants::ATTACK;
    this->sender.send(opCode);
}

void Protocol::pickUp() {
    const uint8_t opCode = ProtocolConstants::PICK_UP_ITEM;
    this->sender.send(opCode);
}

void Protocol::buy(const BuyOrder& buyOrder) {
    const uint8_t opCode = ProtocolConstants::BUY;
    uint8_t buyOrderType = buyOrder.type;
    this->sender.send(opCode);
    this->sender.send(buyOrderType);
    this->sender.send(buyOrder.amount);
}

void Protocol::changeAngle(const double& angle) {
    const uint8_t opCode = ProtocolConstants::CHANGE_ANGLE;
    this->sender.send(opCode);
    this->sender.send(angle);
}

void Protocol::changeWeapon(const WeaponChanger& weaponChanger) {
    const uint8_t opCode = ProtocolConstants::SWITCH_WEAPON;
    this->sender.send(opCode);
    this->sender.send(weaponChanger.weaponSelection);
}

void Protocol::plantBomb() {
    const uint8_t opCode = ProtocolConstants::PLANT_BOMB;
    this->sender.send(opCode);
}

void Protocol::defuseBomb() {
    const uint8_t opCode = ProtocolConstants::DEFUSE_BOMB;
    this->sender.send(opCode);
}

void Protocol::exit() {
    const uint8_t opCode = ProtocolConstants::EXIT_GAME;
    this->sender.send(opCode);
}

PlayerChoicesDTO Protocol::readPlayerChoices() const {
    size_t id = this->reader.readSizeT();
    std::string playerName = this->reader.stringReader();
    Team team = static_cast<Team>(this->reader.u8tReader());
    Skin skin = static_cast<Skin>(this->reader.u8tReader());
    return PlayerChoicesDTO(id, playerName, team, skin);
}

Snapshot Protocol::receiveSnapshot() const {
    std::vector<PlayerInformation> playersInfo;
    Snapshot snapshot = this->reader.readSnapShot();
    return snapshot;
}

PreSnapshot Protocol::receivePreSnapshot() const {
    size_t id = this->reader.readSizeT();
    std::vector<char> tiles = this->reader.bytesReader();
    std::string row;
    std::vector<std::vector<uint8_t>> map;
    std::vector<uint8_t> rowData;
    for (auto& tile: tiles) {
        if (tile == '\n') {
            map.push_back(rowData);
            rowData = std::vector<uint8_t>();
            continue;
        }
        rowData.push_back(tile);
    }

    return {id, map};
}

void Protocol::emptyBullets() { std::cout << "xd\n"; }
