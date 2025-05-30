//
// Created by lionel on 26/05/25.
//

#ifndef PLAYERINFODTO_H
#define PLAYERINFODTO_H
#include <string>
#include <vector>

#include "CoordinateDTO.h"
#include "WeaponInfoDTO.h"

class PlayerInfoDTO {
    size_t id;
    std::string name;
    CoordinateDTO coordinate;
    double angle;
    uint16_t actualMoney;
    uint8_t actualHealthPoints;
    std::vector<WeaponInfoDTO> weaponsInfo;
    WeaponInfoDTO actualWeapon;
    public:
    PlayerInfoDTO(const size_t& id, const std::string& name, const CoordinateDTO& coordinate,
        const double& angle, const uint16_t& actualMoney, const uint8_t& actualHealthPoints,
        std::vector<WeaponInfoDTO>& weaponInfo, WeaponInfoDTO& actualWeaponInfo):
    id(id), name(name), coordinate(coordinate), angle(angle), actualMoney(actualMoney),
    actualHealthPoints(actualHealthPoints), weaponsInfo(std::move(weaponInfo)),
    actualWeapon(std::move(actualWeaponInfo)) {}

    [[nodiscard]] const size_t& getId() const;
    [[nodiscard]]const std::string& getName() const;
    [[nodiscard]]const CoordinateDTO& getCoordinate() const;
    [[nodiscard]]const double& getAngle() const;
    [[nodiscard]]const std::vector<WeaponInfoDTO>& getWeaponsInfo() const;
    [[nodiscard]]const WeaponInfoDTO& getActualWeapon() const;

};

#endif //PLAYERINFODTO_H
