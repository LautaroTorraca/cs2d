//
// Created by lionel on 26/05/25.
//

#include "GameParser.h"

std::map<Coordinate, Path> GameParser::getMapPath() const {
    return this->gameMapParser.getMapPath();
}

std::vector<std::vector<uint8_t>> GameParser::getMap() const {
    return this->gameMapParser.getMap();
}

std::vector<Coordinate> GameParser::getCountersSpawnPoints() const {
    return this->gameMapParser.getCountersSpawnPoints();
}

std::vector<Coordinate> GameParser::getTerroristsSpawnPoints() const {
    return this->gameMapParser.getTerroristsSpawnPoints();
}

std::vector<Coordinate> GameParser::getBombPlantPoints() const {
    return this->gameMapParser.getBombPlantPoints();
}

std::map<ProductType, std::unique_ptr<Factory>> GameParser::getShopFactories() {
    return this->shopParser.getShopFactories(this->weaponsInfoParser);
}

double GameParser::getGameInfo(const std::string &key) const {
    return this->gameInfoParser.getGameInfo(key);
}
double GameParser::getGameMapInfo(const std::string &key) const {
    return this->gameInfoParser.getGameMapInfo(key);
}
double GameParser::getPlayerInfo(const std::string &key) const {
    return this->gameInfoParser.getPlayerInfo(key);
}

double GameParser::getWeaponInfo(const WeaponType &type, const std::string &info) const {
    return this->weaponsInfoParser.getWeaponInfo(type, info);
}
