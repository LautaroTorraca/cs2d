//
// Created by lionel on 25/05/25.
//

#include "GameMap.h"

void GameMap::collisionWithAll(const Coordinate& point, const std::shared_ptr<Entity>& entity) {
    Coordinate coordinate;
    coordinate.update(point);
    for (auto& positionedEntity : this->entities[std::move(coordinate)]) {
        entity->collision(*positionedEntity);
    }
}

void GameMap::putOut(std::shared_ptr<Entity> &entity) {
    Coordinate coordinate;
    Position actualPosition = entity->displaced(coordinate);
    std::vector<Coordinate> actualZone = actualPosition.getArea();

    for ( Coordinate& actualPoint: actualZone ) {
        if ( this->entities.contains(actualPoint) ) {
            std::vector<std::shared_ptr<Entity>>& entitiesInPoint = this->entities.at(actualPoint);
            std::erase(entitiesInPoint, entity);
            if ( this->entities.at(actualPoint).empty() )
                this->entities.erase(actualPoint);
        }
    }
}

void GameMap::setNewPosition(std::shared_ptr<Entity> &entity) {
    Coordinate noDisplacement;
    Position actualPosition = entity->displaced(noDisplacement);
    std::vector<Coordinate> actualZone = actualPosition.getArea();
    for (auto& zonePoint: actualZone) {
        Coordinate point;
        point.update(zonePoint);
        this->entities[std::move(point)].emplace_back(entity);
    }
}

void GameMap::collision(std::shared_ptr<Entity> &entity, const Coordinate& displacement) {
    Position newPosition =  entity->displaced(displacement);
    entity->allocate(newPosition);
    std::vector<Coordinate> displacedZone = newPosition.getArea();
    for (auto& zonePoint : displacedZone) {
        Coordinate tileCoordinate = zonePoint.getSector();
        if (!this->pathTiles.contains(tileCoordinate)) {
            entity->collision();
        }
        if (this->entities.contains(zonePoint)) {
            this->collisionWithAll(zonePoint, entity);
        }
    }
}

void GameMap::returnToInitialPosition(const std::shared_ptr<Entity> &entity) {
    Coordinate coordinate;
    Position actualPosition = entity->displaced(coordinate);
    std::vector<Coordinate> actualZone = actualPosition.getArea();
    for ( Coordinate& actualPoint: actualZone ) {
        this->entities[std::move(actualPoint)].emplace_back(entity);
    }
}

void GameMap::move(std::shared_ptr<Entity>& entity, const Coordinate &displacement) {
    this->putOut(entity);
    this->collision(entity, displacement);
    this->setNewPosition(entity);
}

std::vector<std::shared_ptr<Drop>> GameMap::getActualDropsInArea(const Position &position) {
    //TODO: Esto tiene el bug de que los counter tambien pueden agarrar la bomba, ver como manejarlo.
    //TODO: Ademas, refactorizar esto.
    std::vector<Coordinate> area = position.getArea();
    std::vector<std::shared_ptr<Drop>> actualDrops;
    for (auto& point: area) {
        if (this->weaponsDrops.contains(point)) {
            if ( std::find(actualDrops.begin(), actualDrops.end(), this->weaponsDrops.at(point).front()) == actualDrops.end() ) {
                actualDrops.insert(actualDrops.end(), this->weaponsDrops.at(point).begin(),
                                   this->weaponsDrops.at(point).end());
            }
        }
    }
    for (auto& drop: actualDrops) {
        for (auto& point : this->dropToCoordinates.at(drop)) {
            this->weaponsDrops.at(point).erase(std::find(this->weaponsDrops.at(point).begin(), this->weaponsDrops.at(point).end(), drop));
            if (this->weaponsDrops.at(point).empty()) {
                this->weaponsDrops.erase(point);
            }

        }
        this->dropToCoordinates.erase(drop);
    }
    return actualDrops;
}

void GameMap::giveDrops(Inventory &inventory, const Position& position) {
    std::vector<std::shared_ptr<Drop>> actualDrops = this->getActualDropsInArea(position);
    for (auto& drop: actualDrops) {
        drop->giveTo(inventory);
    }

}

void GameMap::place(std::shared_ptr<Drop> &drop, Position &position) {
    std::vector<Coordinate> area = position.getArea();
    for (auto& point: area) {
        Coordinate coordinate;
        coordinate.update(point);
        this->weaponsDrops[std::move(coordinate)].emplace_back(drop);
        this->dropToCoordinates[drop].emplace_back(std::move(point));
    }
}

void GameMap::spawn(std::shared_ptr<Entity> &entity, std::vector<Coordinate>& spawnPositions) {
    Coordinate referencePoint(std::move(spawnPositions.back()));
    referencePoint = std::move(referencePoint*TILE_SIZE);
    Position initialPosition(referencePoint, TILE_SIZE, TILE_SIZE);
    spawnPositions.pop_back();
    entity->allocate(initialPosition);
    for (Coordinate& point: initialPosition.getArea()) {
        this->entities[std::move(point)].emplace_back(entity);
    }
}

void GameMap::spawnCounter(std::shared_ptr<Entity> &entity) {
    this->spawn(entity, this->countersSpawnPoints);
}

void GameMap::spawnTerrorist(std::shared_ptr<Entity> &entity) {
    this->spawn(entity, this->terroristsSpawnPoints);
}

std::vector<DropDTO> GameMap::getDrops() const {
    std::vector<DropDTO> actualDrops;
    for ( auto& drop : this->dropToCoordinates) {
        DropDTO dropInfo = drop.first->getInfo();
        actualDrops.emplace_back(std::move(dropInfo));
    }
    return actualDrops;
}
