//
// Created by lionel on 25/05/25.
//

#ifndef GAMEMAP_H
#define GAMEMAP_H
#include <map>
#include <memory>
#include <vector>
#include "Coordinate.h"
#include "Entity.h"
#include "GameParser.h"
#include "Path.h"
#include "DropPlacer.h"

#define TILE_SIZE 32

class GameMap : public Positionable, public DropPlacer {
    std::map<Coordinate, Path> pathTiles;
    std::map<Coordinate, std::vector<std::shared_ptr<Entity>>> entities;
    std::map<Coordinate, std::vector<std::shared_ptr<Drop>>> weaponsDrops;
    std::map<std::shared_ptr<Drop>, std::vector<Coordinate>> dropToCoordinates;
    std::vector<Coordinate> countersSpawnPoints;
    std::vector<Coordinate> terroristsSpawnPoints;
    void spawn(std::shared_ptr<Entity> &entity, std::vector<Coordinate> &spawnPositions);
    void putOut(std::shared_ptr<Entity> &entity);
    void setNewPosition(std::shared_ptr<Entity> &entity);
    void collision(std::shared_ptr<Entity> &entityconst, const Coordinate& displacement);
    void returnToInitialPosition(const std::shared_ptr<Entity> & entity);
    void collisionWithAll(const Coordinate& point, const std::shared_ptr<Entity>& entity);
    std::vector<std::shared_ptr<Drop>> getActualDropsInArea(const Position &position);

public:
    explicit GameMap(const GameParser& parser) : pathTiles(std::move(parser.getMapPath())) , countersSpawnPoints(std::move(parser.getCountersSpawnPoints())), terroristsSpawnPoints(std::move(parser.getTerroristsSpawnPoints())) {}
    void move(std::shared_ptr<Entity>& entity, const Coordinate &displacement) override;
    void giveDrops(Inventory &inventory, const Position &position) override;
    void place(std::shared_ptr<Drop> &drop, Position &position) override;
    void spawnCounter(std::shared_ptr<Entity>& entity);
    void spawnTerrorist(std::shared_ptr<Entity>& entity);
    std::vector<DropDTO> getDrops() const;
    ~GameMap() override = default;
};



#endif //GAMEMAP_H
