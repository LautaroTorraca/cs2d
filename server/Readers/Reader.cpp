
#include "Reader.h"

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include <arpa/inet.h>

#include "client/DropInformation.h"
#include "client/PlayerInformation.h"
#include "server/PlayerStatus.h"

#include "server/ConnectionClosed.h"

#define NEW 0X6E
#define PRECISION 10000

Reader::Reader(Socket& socket): socket(socket) {}

void Reader::bytesChecker(const int& bytesRead) const {
    if (bytesRead == 0) {
        throw ConnectionClosed("Reader Connection closed");
    }
}

uint8_t Reader::u8tReader() const {
    uint8_t result;
    int bytesRead = socket.recvall(&result, sizeof(result));
    this->bytesChecker(bytesRead);
    return result;
}

uint16_t Reader::u16tReader() const {
    uint16_t result;
    int bytesRead = socket.recvall(&result, sizeof(result));
    this->bytesChecker(bytesRead);
    result = ntohs(result);
    return result;
}

std::string Reader::stringReader() const {

    uint16_t nameLength = 0;

    int bytesRead = socket.recvall(&nameLength, sizeof(nameLength));
    this->bytesChecker(bytesRead);
    nameLength = ntohs(nameLength);
    std::vector<char> buffer(nameLength);
    bytesRead = socket.recvall(buffer.data(), nameLength);
    this->bytesChecker(bytesRead);
    std::string str(buffer.begin(), buffer.end());
    return str;
}

std::vector<char> Reader::bytesReader() const {

    uint16_t nameLength = 0;
    int bytesRead = socket.recvall(&nameLength, sizeof(nameLength));
    this->bytesChecker(bytesRead);
    nameLength = ntohs(nameLength);
    std::vector<char> buffer(nameLength);
    bytesRead = socket.recvall(buffer.data(), nameLength);
    this->bytesChecker(bytesRead);
    return buffer;
}

double Reader::doubleRead() const {
    int result;
    int bytesRead = socket.recvall(&result, sizeof(result));
    this->bytesChecker(bytesRead);
    result = ntohl(result);
    return result/PRECISION;
}

size_t Reader::readSizeT() const {
    uint32_t result;
    int bytesRead = socket.recvall(&result, sizeof(result));
    this->bytesChecker(bytesRead);
    result = ntohl(result);
    return result;
}

int Reader::readInt() const {
    int result;
    int bytesRead = this->socket.recvall(&result, sizeof(result));
    this->bytesChecker(bytesRead);
    result = ntohl(result);
    return result;
}

CoordinateInformation Reader::readCoordinateInformation() const {
    double x = this->doubleRead();
    double y = this->doubleRead();
    return CoordinateInformation(x, y);
}

ProjectileInformation Reader::readProjectile() const {
    CoordinateInformation position = this->readCoordinateInformation();
    return ProjectileInformation(position);
}

WeaponInformation Reader::readWeapon() const {
    WeaponType type = static_cast<WeaponType>(this->u8tReader());
    uint16_t ammoAmount = this->u16tReader();
    std::vector<ProjectileInformation> projectiles;
    while (this->u8tReader() == NEW) {
        projectiles.push_back(this->readProjectile());
    }
    return WeaponInformation(type, ammoAmount, projectiles);
}

PlayerInformation Reader::readPlayer() const {
    size_t id = this->readSizeT();
    std::string playerName = this->stringReader();
    double angle = this->doubleRead();
    CoordinateInformation position = this->readCoordinateInformation();
    uint8_t health = this->u8tReader();
    uint16_t money = this->u16tReader();
    uint16_t collectedMoney = this->u16tReader();
    uint8_t kills = this->u8tReader();
    uint8_t deaths = this->u8tReader();
    Skin skin = static_cast<Skin>(this->u8tReader());
    WeaponInformation actualWeapon = this->readWeapon();
    std::vector<WeaponInformation> weapons;
    while (this->u8tReader() == NEW) {
        weapons.push_back(this->readWeapon());
    }
    PlayerStatus status = static_cast<PlayerStatus>(this->u8tReader());
    return PlayerInformation(id, playerName, skin, position, angle, money, collectedMoney, health, weapons,
                             actualWeapon, kills, deaths, status);
}

DropInformation Reader::readDrop() const {
    WeaponInformation weapon = this->readWeapon();
    CoordinateInformation position = this->readCoordinateInformation();
    return DropInformation(weapon, position);
}

std::map<ProductType, double> Reader::readShopInfo() const {
    std::map<ProductType, double> shopInfo;
    while (this->u8tReader() == NEW) {
        ProductType product = static_cast<ProductType>(this->u8tReader());
        double price = this->doubleRead();
        shopInfo.emplace(product, price);
    }
    return shopInfo;
}

Snapshot Reader::readSnapShot() const {
    std::vector<PlayerInformation> playersInfo;
    while (this->u8tReader() == NEW) {
        PlayerInformation playerInfo = this->readPlayer();
        playersInfo.push_back(playerInfo);
    }
    uint8_t currentRound = this->u8tReader();
    uint8_t countersWinsRounds = this->u8tReader();
    uint8_t terroristsWinsRounds = this->u8tReader();
    CoordinateInformation bombPosition = this->readCoordinateInformation();
    double bombTimer = this->doubleRead();
    GameStatus status = static_cast<GameStatus>(this->u8tReader());
    std::vector<DropInformation> drops;
    while (this->u8tReader() == NEW) {
        DropInformation dropInfo = this->readDrop();
        drops.push_back(dropInfo);
    }
    double actualTime = this->doubleRead();
    uint8_t totalRounds = this->u8tReader();
    return Snapshot(status, currentRound, countersWinsRounds, terroristsWinsRounds, playersInfo,
                    drops, bombPosition, bombTimer, actualTime, totalRounds);
}
