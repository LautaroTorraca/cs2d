//
// Created by lionel on 26/05/25.
//
#include "PlayerInfoDTO.h"

const size_t& PlayerInfoDTO::getId() const { return id; }
const std::string& PlayerInfoDTO::getName() const { return name; }
const Skin& PlayerInfoDTO::getSkin() const { return skin; }
const CoordinateDTO& PlayerInfoDTO::getCoordinate() const { return coordinate; }
const double& PlayerInfoDTO::getAngle() const { return angle; }
const uint16_t& PlayerInfoDTO::getMoney() const { return actualMoney; }
const uint8_t& PlayerInfoDTO::getHealth() const { return this->actualHealthPoints; }
const std::vector<WeaponInfoDTO>& PlayerInfoDTO::getWeaponsInfo() const { return weaponsInfo; }
const WeaponInfoDTO& PlayerInfoDTO::getActualWeapon() const { return actualWeapon; }
const uint8_t& PlayerInfoDTO::getKills() const { return this->kills; }
