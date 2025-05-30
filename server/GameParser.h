//
// Created by lionel on 26/05/25.
//

#ifndef GAMEPARSER_H
#define GAMEPARSER_H
#include "GameMapParser.h"
#include "ShopParser.h"
#include "WeaponsInfoParser.h"


class GameParser {
    GameMapParser gameMapParser;
    ShopParser shopParser;
    WeaponsInfoParser weaponsInfoParser;
public:
    explicit GameParser(const std::string& mapFilePath, const std::string& shopFilePath, const std::string& weaponsInfoFilePath) : gameMapParser(mapFilePath), shopParser(shopFilePath), weaponsInfoParser(weaponsInfoFilePath) {}
    GameParser(GameParser&& other) noexcept : gameMapParser(std::move(other.gameMapParser)), shopParser(std::move(other.shopParser)), weaponsInfoParser(std::move(other.weaponsInfoParser)) {}
    [[nodiscard]] std::map<Coordinate, Path> getMapPath() const;
    [[nodiscard]] std::map<Coordinate, Tile> getMap() const;
    [[nodiscard]] std::vector<Coordinate> getCountersSpawnPoints() const;
    [[nodiscard]] std::vector<Coordinate> getTerroristsSpawnPoints() const;
    std::map<ProductTypes, std::unique_ptr<Factory>> getShopFactories();
    double getWeaponInfo(const WeaponType& type, const std::string& info) const;

};



#endif //GAMEPARSER_H
