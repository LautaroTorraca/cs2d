//
// Created by lionel on 26/05/25.
//
#include "PlayerInfoDTO.h"

const size_t& PlayerInfoDTO::getId() const { return id; }
const std::string& PlayerInfoDTO::getName() const { return name; }
const CoordinateDTO& PlayerInfoDTO::getCoordinate() const { return coordinate; }
const double& PlayerInfoDTO::getAngle() const { return angle; }
const std::vector<WeaponInfoDTO> & PlayerInfoDTO::getWeaponsInfo() const { return weaponsInfo; }
const WeaponInfoDTO & PlayerInfoDTO::getActualWeapon() const { return actualWeapon; }
