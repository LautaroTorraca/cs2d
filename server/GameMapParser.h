//
// Created by lionel on 26/05/25.
//

#ifndef GAMEMAPPARSER_H
#define GAMEMAPPARSER_H
#include <functional>
#include <map>
#include <string>

#include "Path.h"
#include "Coordinate.h"
#include "TileType.h"
#include "cmake-build-debug/_deps/fkyaml-src/include/fkYAML/fkyaml_fwd.hpp"

class GameMapParser {
    std::vector<std::vector<uint8_t>> gameMap;
    std::vector<std::map<std::string, double>> terroristsSpawns;
    std::vector<std::map<std::string, double>> countersSpawns;
    std::vector<std::map<std::string, double>> bombPlantPoints;
    std::map<uint8_t, TileType> typeInfo;
    std::map<TileType, std::function<Tile(uint8_t&)>> tileTranslator;

    [[nodiscard]] std::vector<Coordinate> getPoints(std::vector<std::map<std::string, double>> source) const;
    public:
    explicit GameMapParser(const std::string& mapFilePath);
    GameMapParser(GameMapParser&& other) noexcept;
    [[nodiscard]] std::map<Coordinate, Path> getMapPath() const;
    [[nodiscard]] std::map<Coordinate, Tile> getMap() const;
    [[nodiscard]] std::vector<Coordinate> getCountersSpawnPoints() const;
    [[nodiscard]] std::vector<Coordinate> getTerroristsSpawnPoints() const;
    [[nodiscard]] std::vector<Coordinate> getBombPlantPoints() const;
};



#endif //GAMEMAPPARSER_H
