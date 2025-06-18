//
// Created by lionel on 03/06/25.
//

#ifndef PLAYERINFORMATION_H
#define PLAYERINFORMATION_H
#include <cstdint>
#include <string>
#include <vector>

#include "server/Skin.h"

#include "CoordinateInformation.h"
#include "WeaponInformation.h"

struct PlayerInformation {
    size_t id;
    std::string name;
    Skin skin;
    CoordinateInformation position;
    double angle;
    uint16_t actualMoney;
    uint8_t actualHealthPoints;
    std::vector<WeaponInformation> weaponsInfo;
    WeaponInformation actualWeapon;
    std::uint8_t kills;
    PlayerInformation(const size_t& id, const std::string& name, const Skin& skin,
                      const CoordinateInformation& position, const double& angle,
                      const uint16_t& actualMoney, const uint8_t& actualHealthPoints,
                      std::vector<WeaponInformation>& weaponsInfo,
                      const WeaponInformation& actualWeapon, const uint8_t& kills):
            id(id),
            name(name),
            skin(skin),
            position(position),
            angle(angle),
            actualMoney(actualMoney),
            actualHealthPoints(actualHealthPoints),
            weaponsInfo(std::move(weaponsInfo)),
            actualWeapon(actualWeapon),
            kills(kills) {}
};

#endif  // PLAYERINFORMATION_H
