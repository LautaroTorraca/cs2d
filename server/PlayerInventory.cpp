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

PlayerInventory::PlayerInventory(const GameParser &gameParser, DropPlacer& weaponPlacer, Position& position) : weaponPlacer(weaponPlacer), position(position) {
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
}

void PlayerInventory::add(const uint8_t &index, std::shared_ptr<Weapon> &weapon) {
    if ( index > GLOCK_INDEX ) {
        this->drop(index);
        this->weaponSetter.emplace(index, weapon);
    }
}

void PlayerInventory::set(const uint8_t &index, std::shared_ptr<Weapon> &actualWeapon) {
    if (this->weaponSetter.contains(index)) {
        actualWeapon = this->weaponSetter.at(index);
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


