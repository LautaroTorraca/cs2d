//
// Created by lionel on 26/05/25.
//

#include "GameMapParser.h"

#include <iostream>

#include <fkYAML/node.hpp>

#include "AKFactory.h"
#include "Awp.h"
#include "Drop.h"
#include "DropBox.h"
#include "M3.h"
#include "Position.h"
#include "Wall.h"
#include "fstream"

#define GAME_MAP_KEY "gameMap"
#define WALLS_KEY "walls"
#define PATHS_KEY "paths"
#define TERRORISTS_SPAWN_KEY "terroristsSpawnPoints"
#define COUNTERS_SPAWN_KEY "countersSpawnPoints"
#define BOMB_PLANT_POINTS_KEY "bombPlantPoints"
#define DROP_CODE_KEY "weaponCode"
#define DROPS_KEY "drops"
#define X_POSITION "x"
#define Y_POSITION "y"
#define TILE_SIZE 32
#define WEAPON_INFO_PATH "../gameConstants/WeaponsConfig.yaml"
#define M3_SWEPT_ANGLE_KEY "sweptAngle"
#define BURST_SPEED_KEY "burstSpeed"


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
    this->drops = root[DROPS_KEY].get_value<std::vector<std::map<std::string, double>>>();
    this->dropTranslator[1] = [&] (Position& position)->std::shared_ptr<Drop> {
        WeaponsInfoParser parser(WEAPON_INFO_PATH);
        double akDamagePerBullet =  parser.getWeaponInfo(WeaponType::AK47, DAMAGE_PER_BULLET_KEY);
        double akPrecision =  parser.getWeaponInfo(WeaponType::AK47, PRECISION_KEY);
        double akRange =  parser.getWeaponInfo(WeaponType::AK47, RANGE_KEY);
        double akCadence =  parser.getWeaponInfo(WeaponType::AK47, CADENCE_KEY);
        double akSpeed =  parser.getWeaponInfo(WeaponType::AK47, SPEED_KEY);
        double akBulletsPerShot =  parser.getWeaponInfo(WeaponType::AK47, BULLETS_PER_SHOT_KEY);
        double akBurstSpeed =  parser.getWeaponInfo(WeaponType::AK47, BURST_SPEED_KEY);
        double maxBullets =  parser.getWeaponInfo(WeaponType::AK47, MAX_BULLETS_KEY);
        std::shared_ptr<Ak> ak = std::make_shared<Ak>(0, akDamagePerBullet, akPrecision, akRange, akCadence, akSpeed, akBulletsPerShot, akBurstSpeed, maxBullets);
        return std::make_shared<DropBox>(2, ak, position);
    };

    this->dropTranslator[2] = [&] (Position& position)->std::shared_ptr<Drop> {
        WeaponsInfoParser parser(WEAPON_INFO_PATH);
        double m3DamagePerBullet =  parser.getWeaponInfo(WeaponType::M3, DAMAGE_PER_BULLET_KEY);
        double m3Precision =  parser.getWeaponInfo(WeaponType::M3, PRECISION_KEY);
        double m3Range =  parser.getWeaponInfo(WeaponType::M3, RANGE_KEY);
        double m3Cadence =  parser.getWeaponInfo(WeaponType::M3, CADENCE_KEY);
        double m3Speed =  parser.getWeaponInfo(WeaponType::M3, SPEED_KEY);
        double m3BulletsPerShot =  parser.getWeaponInfo(WeaponType::M3, BULLETS_PER_SHOT_KEY);
        double m3SweptAngle = parser.getWeaponInfo(WeaponType::M3, M3_SWEPT_ANGLE_KEY);
        double maxBullets =  parser.getWeaponInfo(WeaponType::M3, MAX_BULLETS_KEY);
        std::shared_ptr<M3> m3 = std::make_shared<M3>(0, m3DamagePerBullet, m3Precision, m3Range, m3Cadence, m3Speed, m3BulletsPerShot, m3SweptAngle, maxBullets);
        return std::make_shared<DropBox>(2, m3, position);
    };

    this->dropTranslator[3] = [&] (Position& position)->std::shared_ptr<Drop> {
        WeaponsInfoParser parser(WEAPON_INFO_PATH);
        double awpDamagePerBullet =  parser.getWeaponInfo(WeaponType::AWP, DAMAGE_PER_BULLET_KEY);
        double awpPrecision =  parser.getWeaponInfo(WeaponType::AWP, PRECISION_KEY);
        double awpRange =  parser.getWeaponInfo(WeaponType::AWP, RANGE_KEY);
        double awpCadence =  parser.getWeaponInfo(WeaponType::AWP, CADENCE_KEY);
        double awpSpeed =  parser.getWeaponInfo(WeaponType::AWP, SPEED_KEY);
        double awpBulletsPerShot =  parser.getWeaponInfo(WeaponType::AWP, BULLETS_PER_SHOT_KEY);
        double maxBullets =  parser.getWeaponInfo(WeaponType::AK47, MAX_BULLETS_KEY);
        std::shared_ptr<Awp> awp = std::make_shared<Awp>(0, awpDamagePerBullet, awpPrecision, awpRange, awpCadence, awpSpeed, awpBulletsPerShot, maxBullets);
        return std::make_shared<DropBox>(2, awp, position);
    };

}

GameMapParser::GameMapParser(GameMapParser &&other) noexcept :
            gameMap(std::move(other.gameMap)),
            terroristsSpawns(std::move(other.terroristsSpawns)),
            countersSpawns(std::move(other.countersSpawns)),
            bombPlantPoints(std::move(other.bombPlantPoints)),
            typeInfo(std::move(other.typeInfo)),
            tileTranslator(std::move(other.tileTranslator)),
            drops(other.drops),
            dropTranslator(other.dropTranslator) {
    other.gameMap = std::vector<std::vector<uint8_t>>();
    other.terroristsSpawns = std::vector<std::map<std::string, double>>();
    other.countersSpawns = std::vector<std::map<std::string, double>>();
    other.bombPlantPoints = std::vector<std::map<std::string, double>>();
    other.typeInfo = std::map<uint8_t, TileType>();
    other.tileTranslator = std::map<TileType, std::function<Tile(uint8_t&)>>();
    other.drops = std::vector<std::map<std::string, double>>();
    other.dropTranslator = std::map<double, std::function<std::shared_ptr<Drop>(Position&)>>();
}

std::map<Coordinate, Path> GameMapParser::getMapPath() const {
    std::map<Coordinate, Path> mapPath;
    for (size_t i = 0; i < gameMap.size(); i++) {
        for (size_t j = 0; j < gameMap[i].size(); j++) {
            uint8_t tile = gameMap[i][j];
            if ( this->typeInfo.contains(tile) && this->typeInfo.at(tile) == PATH_TILE )
                mapPath.emplace(std::move(Coordinate(j, i)), Path(tile));
        }
    }
    return mapPath;
}

std::vector<std::vector<uint8_t>> GameMapParser::getMap() const {
    std::vector<std::vector<uint8_t>> map = this->gameMap;
    return map;
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

uint8_t GameMapParser::getMaxPlayersPerTeam() const {
    size_t maxPlayersPerTeam = std::min(this->getCountersSpawnPoints().size(), this->getTerroristsSpawnPoints().size());
    return maxPlayersPerTeam;
}

std::map<Position, std::shared_ptr<Drop>> GameMapParser::getDrops() const {
    std::map<Position, std::shared_ptr<Drop>> dropsToPlace;
    for (auto&dropInfo : this->drops) {
        Position position(dropInfo.at(X_POSITION)*TILE_SIZE, dropInfo.at(Y_POSITION)*TILE_SIZE, TILE_SIZE, TILE_SIZE);
        std::shared_ptr<Drop> drop = this->dropTranslator.at(dropInfo.at(DROP_CODE_KEY))(position);
        dropsToPlace.emplace(std::move(position), drop);
    }
    return dropsToPlace;
}
