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
#include "Spawner.h"

#define TILE_SIZE 32

class GameMap : public Positionable, public DropPlacer, public Spawner, public Advancer {
    std::map<Coordinate, Path> pathTiles;
    std::map<Coordinate, std::vector<std::shared_ptr<Entity>>> entities;
    std::map<Coordinate, std::vector<std::shared_ptr<Drop>>> weaponsDrops;
    std::map<std::shared_ptr<Drop>, std::vector<Coordinate>> dropToCoordinates;
    std::vector<Coordinate> countersSpawnPoints;
    std::vector<Coordinate> terroristsSpawnPoints;
    std::vector<Coordinate> bombPlantPoints;
    std::map<Position, std::shared_ptr<Explosive>> explosive;
    void spawn(std::shared_ptr<Entity> &entity, std::vector<Coordinate> &spawnPositions);
    void putOut(std::shared_ptr<Entity> &entity);
    void setNewPosition(std::shared_ptr<Entity> &entity);
    void collision(std::shared_ptr<Entity> &entity, const Coordinate& displacement);
    void returnToInitialPosition(const std::shared_ptr<Entity> & entity);
    void collisionWithAll(const Coordinate& point, const std::shared_ptr<Entity>& entity);
    std::vector<std::shared_ptr<Drop>> getActualDropsInArea(const Position &position);

public:
    explicit GameMap(const GameParser& parser) :
    pathTiles(std::move(parser.getMapPath())),
    countersSpawnPoints(std::move(parser.getCountersSpawnPoints())),
    terroristsSpawnPoints(std::move(parser.getTerroristsSpawnPoints())),
    bombPlantPoints(std::move(parser.getBombPlantPoints())) {}
    void move(std::shared_ptr<Entity>& entity, const Coordinate &displacement) override;
    void giveDrops(Inventory &inventory, const Position &position) override;
    void place(std::shared_ptr<Drop> &drop, const Position &position) override;
    void spawnCounter(std::shared_ptr<Entity>& entity) override;
    void spawnTerrorist(std::shared_ptr<Entity>& entity) override;
    void remove(const std::shared_ptr<Entity> &entity) override;
    void deactivate(Position& position, std::shared_ptr<Deactivator>& deactivator) override;
    void plant(std::shared_ptr<Explosive>& explosive, const Position &position) override;
    void advance(const double &actualTime) override;
    [[nodiscard]] std::vector<DropDTO> getDrops() const;
    [[nodiscard]] CoordinateDTO getExplosivePosition() const;
    [[nodiscard]] double getExplosiveTime() const;
    ~GameMap() override = default;
    void reset(GameParser& parser);
};



#endif //GAMEMAP_H
