//
// Created by lionel on 28/05/25.
//

#include "Bomb.h"
#include <iostream>
#define BOMB_INDEX 3
#define PERMISSIVE_RELEASE 0.5

Bomb::Bomb(Bomb && bomb) noexcept : finalizable(bomb.finalizable) {
}

void Bomb::attack(Positionable & positionable, const Position & position, const double &) {
    std::shared_ptr<Explosive> explosive(this, [](Explosive*){});
    positionable.plant(explosive, position);
}

void Bomb::addTo(Inventory &inventory) {
    //TODO: Fijarse si se puede pasar este codigo pseudo-repetido en todas las weapons a la clase padre.
    std::shared_ptr<Weapon> weapon = std::make_shared<Bomb>(std::move(*this));
    inventory.add(BOMB_INDEX, weapon);
}

void Bomb::advance(const double &actualTime) {
    this->actualTime = actualTime;
    if ( this->activationStartTime > 0 && (this->actualTime - this->activationStartTime) >= this->activationDuration ) {
        this->finalizable.terroristsWins();
    }

    if (this->lastDeactivationTime > 0 && (this->actualTime - this->lastDeactivationTime) >= PERMISSIVE_RELEASE) {
        this->deactivationStartTime = 0;
        this->lastDeactivationTime = 0;
    }

    if ( this->deactivationStartTime > 0 && this->actualTime - this->deactivationStartTime >= this->deactivationDuration ) {
        this->finalizable.countersWins();
    }
}

void Bomb::deactivate() {
    if ( this->deactivationStartTime == 0 ) {
        this->deactivationStartTime = this->actualTime;
    }
    this->lastDeactivationTime = this->actualTime;
}

void Bomb::activate() {
    this->owner->release(BOMB_INDEX);
    this->finalizable.bombHasBeenPlanted();
    this->activationStartTime = this->actualTime;
}

WeaponInfoDTO Bomb::getInfo() {
    return {1, WeaponType::BOMB};
}
