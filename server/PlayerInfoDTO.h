//
// Created by lionel on 26/05/25.
//

#ifndef PLAYERINFODTO_H
#define PLAYERINFODTO_H
#include <string>
#include <vector>

#include "CoordinateDTO.h"
#include "PlayerStatus.h"
#include "Skin.h"
#include "WeaponInfoDTO.h"

class PlayerInfoDTO {
    size_t id;
    std::string name;
    Skin skin;
    CoordinateDTO coordinate;
    double angle;
    uint16_t actualMoney;
    uint8_t actualHealthPoints;
    std::vector<WeaponInfoDTO> weaponsInfo;
    WeaponInfoDTO actualWeapon;
    uint8_t kills;
    uint8_t deaths;
    PlayerStatus status;
    public:
    PlayerInfoDTO(const size_t& id, const std::string& name, const Skin& skin, const CoordinateDTO& coordinate,
        const double& angle, const uint16_t& actualMoney, const uint8_t& actualHealthPoints,
        std::vector<WeaponInfoDTO>& weaponInfo, WeaponInfoDTO& actualWeaponInfo, const uint8_t& kills, const uint8_t& deaths, const PlayerStatus& status):
    id(id), name(name), skin(skin), coordinate(coordinate), angle(angle), actualMoney(actualMoney),
    actualHealthPoints(actualHealthPoints), weaponsInfo(std::move(weaponInfo)),
    actualWeapon(std::move(actualWeaponInfo)),
    kills(kills), deaths(deaths), status(status) {}

    [[nodiscard]] const size_t& getId() const;
    [[nodiscard]]const std::string& getName() const;
    [[nodiscard]]const Skin& getSkin() const;
    [[nodiscard]]const CoordinateDTO& getCoordinate() const;
    [[nodiscard]]const double& getAngle() const;
    [[nodiscard]]const uint16_t& getMoney() const;
    [[nodiscard]]const uint8_t& getHealth() const;
    [[nodiscard]]const std::vector<WeaponInfoDTO>& getWeaponsInfo() const;
    [[nodiscard]]const WeaponInfoDTO& getActualWeapon() const;
    [[nodiscard]]const uint8_t& getKills() const;
    [[nodiscard]]const uint8_t& getDeaths() const;
    [[nodiscard]]const PlayerStatus& getStatus() const;

};

#endif //PLAYERINFODTO_H
