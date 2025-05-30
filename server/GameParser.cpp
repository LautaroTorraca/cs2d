//
// Created by lionel on 26/05/25.
//

#include "GameParser.h"

std::map<Coordinate, Path> GameParser::getMapPath() const {
    return this->gameMapParser.getMapPath();
}

std::map<Coordinate, Tile> GameParser::getMap() const {
    return this->gameMapParser.getMap();
}

std::vector<Coordinate> GameParser::getCountersSpawnPoints() const {
    return this->gameMapParser.getCountersSpawnPoints();
}

std::vector<Coordinate> GameParser::getTerroristsSpawnPoints() const {
    return this->gameMapParser.getTerroristsSpawnPoints();
}

std::map<ProductTypes, std::unique_ptr<Factory>> GameParser::getShopFactories() {
    return this->shopParser.getShopFactories(this->weaponsInfoParser);
}

double GameParser::getWeaponInfo(const WeaponType &type, const std::string &info) const {
    return this->weaponsInfoParser.getWeaponInfo(type, info);
}
