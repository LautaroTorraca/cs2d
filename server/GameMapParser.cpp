//
// Created by lionel on 26/05/25.
//

#include "GameMapParser.h"
#include "fstream"
#include <fkYAML/node.hpp>
#include <iostream>

#include "Wall.h"

#define GAME_MAP_KEY "gameMap"
#define WALLS_KEY "walls"
#define PATHS_KEY "paths"
#define TERRORISTS_SPAWN_KEY "terroristsSpawnPoints"
#define COUNTERS_SPAWN_KEY "countersSpawnPoints"
#define BOMB_PLANT_POINTS_KEY "bombPlantPoints"
#define X_POSITION "x"
#define Y_POSITION "y"


GameMapParser::GameMapParser(const std::string &mapFilePath) {
    std::ifstream file(mapFilePath.c_str());
    fkyaml::node root = fkyaml::node::deserialize(file);
    this->tileTranslator.emplace(WALL_TILE, [&] (const uint8_t& code)->Tile {return Wall(code);});
    this->tileTranslator.emplace(PATH_TILE, [&] (const uint8_t& code)->Tile {return Path(code);});
    this->tileTranslator.emplace(EMPTY_TILE, [&] (const uint8_t& code)->Tile { return {code};});
    this->gameMap = root[GAME_MAP_KEY].get_value<std::vector<std::vector<uint8_t>>>();
    auto walls = root[WALLS_KEY].get_value<std::vector<uint8_t>>();
    for (auto wall : walls) {
        this->typeInfo.emplace(wall, WALL_TILE);
    }

    auto paths = root[PATHS_KEY].get_value<std::vector<uint8_t>>();

    for (auto path : paths) {
        this->typeInfo.emplace(path, PATH_TILE);
    }

    this->terroristsSpawns = root[TERRORISTS_SPAWN_KEY].get_value<std::vector<std::map<std::string, double>>>();
    this->countersSpawns = root[COUNTERS_SPAWN_KEY].get_value<std::vector<std::map<std::string, double>>>();
    this->bombPlantPoints = root[BOMB_PLANT_POINTS_KEY].get_value<std::vector<std::map<std::string, double>>>();

}

GameMapParser::GameMapParser(GameMapParser &&other) noexcept :
            gameMap(std::move(other.gameMap)),
            terroristsSpawns(std::move(other.terroristsSpawns)),
            countersSpawns(std::move(other.countersSpawns)),
            bombPlantPoints(std::move(other.bombPlantPoints)),
            typeInfo(std::move(other.typeInfo)) {
    //TODO: Implementar lo que le pasa a other
}

std::map<Coordinate, Path> GameMapParser::getMapPath() const {
    std::map<Coordinate, Path> mapPath;
    for (size_t i = 0; i < gameMap.size(); i++) {
        for (size_t j = 0; j < gameMap[i].size(); j++) {
            uint8_t tile = gameMap[i][j];
            if ( this->typeInfo.contains(tile) && this->typeInfo.at(tile) == PATH_TILE )
                mapPath.emplace(std::move(Coordinate(j, i)), Path(tile)); // TODO: Mirar lo del narrow convertion a double de j, i.
        }
    }
    return mapPath;
}

std::map<Coordinate, Tile> GameMapParser::getMap() const {

    std::map<Coordinate, Tile> mapPath;

    for (size_t i = 0; i < gameMap.size(); i++) {
        for (size_t j = 0; j < gameMap[i].size(); j++) {
            uint8_t tile = gameMap[i][j];
            TileType type = this->typeInfo.at(tile);
            mapPath.emplace(std::move(Coordinate(j, i)), this->tileTranslator.at(type)(tile));
        }
    }

    return mapPath;
}

std::vector<Coordinate> GameMapParser::getPoints(std::vector<std::map<std::string, double>> source) const {
    std::vector<Coordinate> spawnPoints;
    for ( auto& coord : source ) {
        spawnPoints.emplace_back(coord.at(X_POSITION), coord.at(Y_POSITION));
    }
    return spawnPoints;
}


std::vector<Coordinate> GameMapParser::getCountersSpawnPoints() const {
    return this->getPoints(this->countersSpawns);
}

std::vector<Coordinate> GameMapParser::getTerroristsSpawnPoints() const {
    return this->getPoints(this->terroristsSpawns);
}

std::vector<Coordinate> GameMapParser::getBombPlantPoints() const {
    return this->getPoints(this->bombPlantPoints);
}
