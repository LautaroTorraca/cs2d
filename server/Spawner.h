//
// Created by lionel on 31/05/25.
//

#ifndef SPAWNER_H
#define SPAWNER_H
#include <memory>

#include "Entity.h"

class Spawner {
public:
    virtual ~Spawner() = default;

    virtual void spawnCounter(std::shared_ptr<Entity>& entity) = 0;
    virtual void spawnTerrorist(std::shared_ptr<Entity>& entity) = 0;
};

#endif //SPAWNER_H
