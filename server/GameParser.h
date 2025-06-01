//
// Created by lionel on 26/05/25.
//

#ifndef GAMEPARSER_H
#define GAMEPARSER_H
#include "GameInfoParser.h"
#include "GameMapParser.h"
#include "ShopParser.h"
#include "WeaponsInfoParser.h"

#define GAME_INFO_PATH "../gameConstants/GameInfo.yaml"
class GameParser {
    GameMapParser gameMapParser;
    ShopParser shopParser;
    WeaponsInfoParser weaponsInfoParser;
    GameInfoParser gameInfoParser;
public:
    explicit GameParser(const std::string& mapFilePath, const std::string& shopFilePath, const std::string& weaponsInfoFilePath) : gameMapParser(mapFilePath), shopParser(shopFilePath), weaponsInfoParser(weaponsInfoFilePath), gameInfoParser(GAME_INFO_PATH) {}
    GameParser(GameParser&& other) noexcept : gameMapParser(std::move(other.gameMapParser)), shopParser(std::move(other.shopParser)), weaponsInfoParser(std::move(other.weaponsInfoParser)), gameInfoParser(std::move(other.gameInfoParser)) {}
    [[nodiscard]] std::map<Coordinate, Path> getMapPath() const;
    [[nodiscard]] std::map<Coordinate, Tile> getMap() const;
    [[nodiscard]] std::vector<Coordinate> getCountersSpawnPoints() const;
    [[nodiscard]] std::vector<Coordinate> getTerroristsSpawnPoints() const;
    [[nodiscard]] std::vector<Coordinate> getBombPlantPoints() const;
    std::map<ProductType, std::unique_ptr<Factory>> getShopFactories();
    double getGameInfo(const std::string& key) const;
    double getPlayerInfo(const std::string& key) const;
    double getGameMapInfo(const std::string& key) const;
    double getWeaponInfo(const WeaponType& type, const std::string& info) const;

};



#endif //GAMEPARSER_H
