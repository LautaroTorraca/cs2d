//
// Created by lionel on 15/05/25.
//

#include "PlayerInventory.h"
#include <ranges>
#include "DropBox.h"
#include "Glock.h"
#include "Knife.h"

#define PRIMARY_INDEX 2
#define BOMB_INDEX 3

std::vector<WeaponInfoDTO> PlayerInventory::getWeaponsInfo() {
    std::vector<WeaponInfoDTO> weaponsInfo;
    for (auto &weapon: this->weaponSetter | std::views::values) {
        weaponsInfo.emplace_back(weapon->getInfo());
    }
    return weaponsInfo;
}

void PlayerInventory::erase(const uint8_t &index) {
    this->weaponSetter.erase(index);
}

std::vector<uint8_t> PlayerInventory::getIndexes() {
    std::vector<uint8_t> indexes;
    for (const auto &index: this->weaponSetter | std::views::keys) {
        indexes.push_back(index);
    }
    return indexes;
}

void PlayerInventory::reset() {
    std::vector<uint8_t> indexes = this->getIndexes();
    for (const auto &index : indexes) {
        if (index > GLOCK_INDEX) {
            this->drop(index);
        }
    }
}

PlayerInventory::PlayerInventory(const GameParser &gameParser, DropPlacer& weaponPlacer, Position& position, std::shared_ptr<Weapon>& weaponInHands) : weaponPlacer(weaponPlacer), position(position), weaponInHands(weaponInHands) {
    double knifeMinDamage = gameParser.getWeaponInfo(WeaponType::KNIFE, MIN_DAMAGE_KEY);
    double knifeMaxDamage = gameParser.getWeaponInfo(WeaponType::KNIFE, MAX_DAMAGE_KEY);
    double knifeSpeed = gameParser.getWeaponInfo(WeaponType::KNIFE, SPEED_KEY);
    double knifeRange = gameParser.getWeaponInfo(WeaponType::KNIFE, RANGE_KEY);
    this->weaponSetter.emplace(KNIFE_INDEX, std::make_shared<Knife>(knifeMinDamage, knifeMaxDamage, knifeSpeed, knifeRange));

    double glockDamagePerBullet = gameParser.getWeaponInfo(WeaponType::GLOCK, DAMAGE_PER_BULLET_KEY);
    double glockPrecision = gameParser.getWeaponInfo(WeaponType::GLOCK, PRECISION_KEY);
    double glockRange = gameParser.getWeaponInfo(WeaponType::GLOCK, RANGE_KEY);
    double glockCadence = gameParser.getWeaponInfo(WeaponType::GLOCK, CADENCE_KEY);
    double glockSpeed = gameParser.getWeaponInfo(WeaponType::GLOCK, SPEED_KEY);
    double glockBulletsPerShot = gameParser.getWeaponInfo(WeaponType::GLOCK, BULLETS_PER_SHOT_KEY);
    this->weaponSetter.emplace(GLOCK_INDEX, std::make_shared<Glock>(glockDamagePerBullet, glockPrecision, glockRange, glockCadence, glockSpeed, glockBulletsPerShot));

    this->weaponSetter.at(KNIFE_INDEX)->set(this->owner);
    this->weaponSetter.at(GLOCK_INDEX)->set(this->owner);
}

void PlayerInventory::add(const uint8_t &index, std::shared_ptr<Weapon> &weapon) {
    if ( index > GLOCK_INDEX ) {
        this->drop(index);
        this->weaponSetter.emplace(index, weapon);
        weapon->set(this->owner);
        this->set(index);
    }
    if (std::ranges::find(this->bannedObjects, index) != this->bannedObjects.end()) {
        this->drop(index);
        this->set(GLOCK_INDEX);
    }
}

void PlayerInventory::set(const uint8_t &index) {
    if (this->weaponSetter.contains(index)) {
       this->weaponInHands = this->weaponSetter.at(index);
    }
}

void PlayerInventory::drop(const uint8_t &index) {
    if (this->weaponSetter.contains(index)) {
        std::shared_ptr<Drop> drop = std::make_shared<DropBox>(index, this->weaponSetter.at(index), this->position);
        this->weaponPlacer.place(drop, this->position);
        this->weaponSetter.erase(index);
    }
}

void PlayerInventory::recharge(const uint8_t &index, uint16_t &ammoAmount) {
    if (this->weaponSetter.contains(index)) {
        this->weaponSetter.at(index)->recharge(ammoAmount);
    }
}

void PlayerInventory::addBanned(const uint8_t &index) {
    this->bannedObjects.emplace_back(index);
}

void PlayerInventory::setOwner(const std::shared_ptr<Owner> &owner) {
    this->owner = owner;
    for (auto& weapon : this->weaponSetter | std::ranges::views::values) {
        weapon->set(owner);
    }
}

std::vector<uint8_t> PlayerInventory::getKeysCopy() {
    std::vector<uint8_t> keys;
    for (auto &weaponIndex: this->weaponSetter | std::views::keys) {
        keys.emplace_back(weaponIndex);
    }
    return keys;
}

void PlayerInventory::advance(const double &actualTime) {
    std::vector<uint8_t> keys = this->getKeysCopy();
    for (auto& key: keys) {
        if (weaponSetter.contains(key)) {
            this->weaponSetter.at(key)->advance(actualTime);
        }
    }
}


