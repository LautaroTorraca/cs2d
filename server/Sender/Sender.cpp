#include "Sender.h"

#include <cstdint>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include <netinet/in.h>

#include "common/socket.h"
#define NEW 0x6E
#define STOP 0X73

void Sender::bytesChecker(const int& sendBytes) {
    if (sendBytes == 0) {
        throw std::runtime_error("Connection closed");  // TODO HACERLO mas FANCY (socket cerrado)
    }
}

void Sender::send(const std::vector<std::vector<uint8_t>>& map) {
    std::stringstream mapCreator;
    for (const auto& row: map) {
        for (const auto& cell: row) {
            mapCreator << cell;
        }
        mapCreator << std::endl;
    }
    this->send(mapCreator.str());
}

void Sender::send(const PlayerInfoDTO& playerInfo) {
    uint8_t skin = playerInfo.getSkin();
    this->send(playerInfo.getId());
    this->send(playerInfo.getName());
    this->send(playerInfo.getAngle());
    this->send(playerInfo.getCoordinate());
    this->send(playerInfo.getHealth());
    this->send(playerInfo.getMoney());
    this->send(playerInfo.getKills());
    this->send(skin);
    this->send(playerInfo.getActualWeapon());
    for (auto& weaponInfo: playerInfo.getWeaponsInfo()) {
        uint8_t newWeapon = NEW;
        this->send(newWeapon);
        this->send(weaponInfo);
    }
    uint8_t stop = STOP;
    this->send(stop);
}

void Sender::send(const WeaponInfoDTO& weaponInfo) {
    uint8_t type = static_cast<uint8_t>(weaponInfo.getWeaponType());
    this->send(type);
    this->send(weaponInfo.getAmmoAmount());
    for (auto& projectileInfo: weaponInfo.getProjectilesInfo()) {
        uint8_t newProjectile = NEW;
        this->send(newProjectile);
        this->send(projectileInfo);
    }
    uint8_t stop = STOP;
    this->send(stop);
}

void Sender::send(const ProjectileDTO& projectileInfo) {
    this->send(projectileInfo.getCoordinateDTO());
}

void Sender::send(const CoordinateDTO& coordinate) {
    this->send(coordinate.getX());
    this->send(coordinate.getY());
}

void Sender::send(const double& data) {
    int sendableData = data;
    sendableData = htonl(sendableData);
    int sendBytes = this->socket.sendall(&sendableData, sizeof(sendableData));
    this->bytesChecker(sendBytes);
}

void Sender::send(const DropDTO& drop) {
    this->send(drop.getDropInfo());
    this->send(drop.getPosition());
}

void Sender::send(const std::string& data) {

    uint16_t dataLength = data.size();
    std::cout << "data size adentor de send: " << std::to_string(dataLength) << "\n";
    dataLength = htons(dataLength);
    int sendBytes = socket.sendall(&dataLength, sizeof(dataLength));
    this->bytesChecker(sendBytes);
    sendBytes = socket.sendall(&data, data.size());
    this->bytesChecker(sendBytes);
}

void Sender::send(const uint8_t& data) {
    int sendBytes = socket.sendall(&data, sizeof(data));
    this->bytesChecker(sendBytes);
}

void Sender::send(const uint16_t& data) {
    uint16_t numberToSend = htons(data);
    int sendBytes = socket.sendall(&numberToSend, sizeof(numberToSend));
    this->bytesChecker(sendBytes);
}

void Sender::send(const size_t& data) {
    uint32_t numberToSend = htonl(data);
    int sendBytes = socket.sendall(&numberToSend, sizeof(numberToSend));
    this->bytesChecker(sendBytes);
}
