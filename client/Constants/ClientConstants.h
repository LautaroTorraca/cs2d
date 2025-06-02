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

inline void fillDummies(Snapshot &gameSnapshot) {

  std::vector<DTO::PlayerData> playerList;
  // tileMap[14][10] = 60;
  // tileMap[14][11] = 61;
  // tileMap[14][12] = 62;
  // std::vector<std::vector<int>> tileMap;

  PlayerData player1;
  PlayerData player2;
  PlayerData player3;

  player1.nombre = "Juan";
  player1.id = 1234;
  player1.coords.x = 50; // RES_WIDTH / 2;
  player1.coords.y = 50; // RES_HEIGTH / 2;
  player1.stats = {100, 50};
  player1.angle = 0;
  player1.skin = GameConstants::Skins::ARCTIC_AVENGER;
  player1.team = GameConstants::Team::COUNTER_TERRORISTS;

  player2.nombre = "Ana";
  player2.id = 5678;
  player2.coords.x = 155;
  player2.coords.y = player1.coords.y - 5;
  player2.stats = {80, 60};
  player2.angle = 120;
  player2.skin = GameConstants::Skins::GUERRILLA;
  player2.team = GameConstants::Team::TERRORISTS;

  player3.nombre = "Ana222";
  player3.id = 568;
  player3.coords.x = player1.coords.x - 25;
  player3.coords.y = player1.coords.y - 25;
  player3.stats = {80, 60};
  player3.angle = 270;
  player3.skin = GameConstants::Skins::L337_KREW;
  player3.team = GameConstants::Team::TERRORISTS;

  playerList.push_back(player1);
  playerList.push_back(player2);
  playerList.push_back(player3);

  gameSnapshot.game.players = playerList;
  // aca seteo que tan a la izquierda se va
  // el mapa cuando arranca a renderizar
  // gameSnapshot.offset.y = 0; // TILE_HEIGHT * 4;
  // gameSnapshot.offset.x = 0; // TILE_WIDTH * 4;

  std::vector<DroppedWeaponDTO> weaponList;

  DroppedWeaponDTO ak_1;
  ak_1.id = WeaponConstants::AK47;
  ak_1.pos.x = 30;
  ak_1.pos.y = 25;
  ak_1.angle = 0;
  DroppedWeaponDTO ak_2;
  ak_2.id = WeaponConstants::AK47;
  ak_2.pos.x = 15;
  ak_2.pos.y = 40;
  ak_2.angle = 220;
  DroppedWeaponDTO m3_1;
  m3_1.id = WeaponConstants::M3;
  m3_1.pos.x = 80;
  m3_1.pos.y = 110;
  m3_1.angle = 330;
  DroppedWeaponDTO glock_1;
  glock_1.id = WeaponConstants::GLOCK;
  glock_1.pos.x = 300;
  glock_1.pos.y = 10;
  glock_1.angle = 60;
  DroppedWeaponDTO bomb;
  bomb.id = WeaponConstants::BOMB;
  bomb.pos.x = 190;
  bomb.pos.y = 130;
  bomb.angle = 60;
  DroppedWeaponDTO awp;
  awp.id = WeaponConstants::AWP;
  awp.pos.x = 130;
  awp.pos.y = 190;
  awp.angle = 60;

  weaponList.push_back(ak_1);
  weaponList.push_back(m3_1);
  weaponList.push_back(glock_1);
  weaponList.push_back(ak_2);
  weaponList.push_back(bomb);
  weaponList.push_back(awp);

  gameSnapshot.game.map.droppedWeapons = weaponList;
}
