//
// Created by lionel on 26/05/25.
//

#ifndef GAMEMAPPARSER_H
#define GAMEMAPPARSER_H
#include <functional>
#include <map>
#include <string>

#include "GameLogic/Interfaces/Drop.h"
#include "GameLogic/Utils/Coordinate.h"
#include "GameLogic/Utils/Path.h"
#include "GameLogic/Utils/TileType.h"

#include "WeaponsInfoParser.h"
class GameMapParser {
    std::vector<std::vector<uint8_t>> gameMap;
    std::vector<std::map<std::string, double>> terroristsSpawns;
    std::vector<std::map<std::string, double>> countersSpawns;
    std::vector<std::map<std::string, double>> bombPlantPoints;
    std::map<uint8_t, TileType> typeInfo;
    std::map<TileType, std::function<Tile(uint8_t&)>> tileTranslator;
    std::vector<std::map<std::string, double>> drops;
    std::map<double, std::function<std::shared_ptr<Drop>(Position&)>> dropTranslator;


    [[nodiscard]] std::vector<Coordinate> getPoints(
            std::vector<std::map<std::string, double>> source) const;

public:
    explicit GameMapParser(const std::string& mapFilePath);
    GameMapParser(GameMapParser&& other) noexcept;
    [[nodiscard]] std::map<Coordinate, Path> getMapPath() const;
    [[nodiscard]] std::vector<std::vector<uint8_t>> getMap() const;
    [[nodiscard]] std::vector<Coordinate> getCountersSpawnPoints() const;
    [[nodiscard]] std::vector<Coordinate> getTerroristsSpawnPoints() const;
    [[nodiscard]] std::vector<Coordinate> getBombPlantPoints() const;
    [[nodiscard]] uint8_t getMaxPlayersPerTeam() const;
    std::map<Position, std::shared_ptr<Drop>> getDrops() const;
};


#endif  // GAMEMAPPARSER_H
