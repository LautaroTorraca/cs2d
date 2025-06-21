//
// Created by lionel on 28/05/25.
//

#include "Bomb.h"

#include <iostream>

#include "Deactivator.h"
#define BOMB_INDEX 3
#define PERMISSIVE_RELEASE 0.5

Bomb::Bomb(Bomb && bomb) noexcept : finalizable(bomb.finalizable) {
}

void Bomb::attack(Positionable & positionable, const Position & position, const double &) {
    std::shared_ptr<Bomb> bombClone = std::make_shared<Bomb>(this->finalizable, this->activationDuration, this->deactivationDuration);
    bombClone->set(this->owner);
    std::shared_ptr<Explosive> explosive = bombClone;
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
        this->finalizable.bombExploded();
    }

    if (this->lastDeactivationTime > 0 && (this->actualTime - this->lastDeactivationTime) >= PERMISSIVE_RELEASE) {
        this->deactivationStartTime = 0;
        this->lastDeactivationTime = 0;
        this->deactivator->deactivatingStopped();
        this->deactivator.reset();
    }

    if ( this->deactivationStartTime > 0 && this->actualTime - this->deactivationStartTime >= this->deactivationDuration ) {
        this->finalizable.countersWins();
    }
}

void Bomb::deactivate(std::shared_ptr<Deactivator>& deactivator) {
    if ( this->deactivationStartTime == 0 ) {
        this->deactivationStartTime = this->actualTime;
    }
    if (this->deactivator) this->deactivator->deactivatingStopped();
    this->deactivator = deactivator;
    this->deactivator->deactivating();
    this->lastDeactivationTime = this->actualTime;
}

void Bomb::activate() {
    this->owner->release(BOMB_INDEX);
    this->finalizable.bombHasBeenPlanted();
    this->activationStartTime = this->actualTime;
}
void Bomb::continueActivation(const double& actualTime) {
    if (this->activationStartTime == 0) this->activationStartTime = actualTime;
    this->advance(actualTime);
}

WeaponInfoDTO Bomb::getInfo() {
    return {1, WeaponType::BOMB};
}
