//
// Created by lionel on 29/05/25.
//

#ifndef WEAPONPLACER_H
#define WEAPONPLACER_H
#include <memory>

#include "GameLogic/Utils/Position.h"

#include "Drop.h"

class DropPlacer {
public:
    virtual ~DropPlacer() = default;

    virtual void place(std::shared_ptr<Drop>& drop, const Position& position) = 0;
    virtual void giveDrops(Inventory &inventory, const Position& position) = 0;
};

#endif //WEAPONPLACER_H
