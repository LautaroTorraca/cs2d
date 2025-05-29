#pragma once

#include "MapTypeConstants.h"
#include <cstdint>

constexpr uint8_t INVALID_OPCODE = 0x00;

constexpr char DEFAULT_GAME_NAME[] = "";

constexpr uint8_t DEFAULT_TEAM_ID = 0;
constexpr uint8_t DEFAULT_SKIN_ID = 0;
constexpr uint8_t DEFAULT_PLAYER_COUNT = 0;
constexpr uint8_t DEFAULT_ROUND_COUNT = 0;
constexpr uint16_t DEFAULT_DIRECTION = 0;
constexpr uint8_t DEFAULT_CLIENT_ID = 0;
constexpr uint8_t DEFAULT_PLAYER_ID = 0;
constexpr uint8_t DEFAULT_ITEM = 0;
constexpr uint8_t DEFAULT_WEAPON_INFORMATION = 0;
constexpr uint16_t DEFAULT_AMMO = 0;

constexpr uint8_t DEFAULT_GAME_MAP_TYPE = static_cast<uint8_t>(MapType::DUMMY);
