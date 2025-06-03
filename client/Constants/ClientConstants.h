#pragma once

#include "Constants/SnapshotConstants.h"
constexpr int RES_WIDTH = 1280;
constexpr int RES_HEIGTH = 720;

constexpr int LOGICAL_WIDTH = 27;
constexpr int LOGICAL_HEIGHT = 15;

constexpr int MAP_WIDTH = 100;
constexpr int MAP_HEIGHT = 60;

constexpr int TILE_SRC_SIZE = 32;
constexpr int TILE_WIDTH = RES_WIDTH / LOGICAL_WIDTH;
constexpr int TILE_HEIGHT = RES_HEIGTH / LOGICAL_HEIGHT;

constexpr int PLAYER_HEIGTH = RES_WIDTH / LOGICAL_WIDTH;
constexpr int PLAYER_WIDTH = RES_HEIGTH / LOGICAL_HEIGHT;

constexpr double WPN_SZ_MULT = 1.3;

enum Ui_type : uint8_t { NumsUI, SymbUI, CursorUI };

using namespace DTO;
