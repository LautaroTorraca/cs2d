#pragma once

// #include "Constants/SnapshotConstants.h"
#include <cstddef>
#include <cstdint>
#include <string>

#include "client/CoordinateInformation.h"
#include "client/ProjectileInformation.h"
#include "SnapshotConstants.h"
constexpr int RES_WIDTH = 1280;
constexpr int RES_HEIGTH = 720;

constexpr int LOGICAL_WIDTH = 27;
constexpr int LOGICAL_HEIGHT = 15;

constexpr int MAP_WIDTH = 11;
constexpr int MAP_HEIGHT = 6;

constexpr int TILE_SRC_SIZE = 32;
constexpr int TILE_WIDTH = RES_WIDTH / LOGICAL_WIDTH;
constexpr int TILE_HEIGHT = RES_HEIGTH / LOGICAL_HEIGHT;

constexpr int PLAYER_HEIGTH = RES_WIDTH / LOGICAL_WIDTH;
constexpr int PLAYER_WIDTH = RES_HEIGTH / LOGICAL_HEIGHT;

constexpr double WPN_SZ_MULT = 1.3;

#define HUD_NUM_H 42
#define HUD_NUM_W 30

enum UiSymbol : int {
    HEALTH = 0,
    SHIELD = 1,
    TIMER = 2,
    PLIER = 3,
    BUY = 4,
    TARGET = 5,
    IDK = 6,
    MONEY = 7,
    PING = 8,
    ARROW = 9,
    BUBBLE = 10,
    INFINITE = 11,
    DEATH = 12
};

enum UiType : uint8_t { NumsUI, SymbUI, CursorUI };

// using namespace DTO;

inline void fillDummies(Snapshot& gameSnapshot) {

    std::vector<PlayerInformation> playerList;
    // tileMap[14][10] = 60;
    // tileMap[14][11] = 61;
    // tileMap[14][12] = 62;
    // std::vector<std::vector<int>> tileMap;


    std::string p1_nombre = "Juan";
    size_t p1_id = 1234;
    CoordinateInformation p1_coords(50, 50);
    double p1_angle = 0;
    Skin p1_skin = Skin::ARCTIC_AVENGER;
    uint16_t p1_actualMoney = 500;
    uint8_t p1_actualHealthPoints = 100;
    std::vector<WeaponInformation> p1_weaponsInfo{};
    WeaponInformation p1_actualWeapon(WeaponType::AK47, 50, {});
    std::uint8_t p1_kills = 1;
    // p1_team = GameConstants::Team::COUNTER_TERRORISTS;

    std::string p2_nombre = "Ana";
    size_t p2_id = 4321;
    CoordinateInformation p2_coords(50, 50);
    double p2_angle = 0;
    Skin p2_skin = Skin::UK_SAS;
    uint16_t p2_actualMoney = 500;
    uint8_t p2_actualHealthPoints = 100;
    std::vector<WeaponInformation> p2_weaponsInfo{};
    ProjectileInformation p2_bullet1({500, 500});
    WeaponInformation p2_actualWeapon(WeaponType::AK47, 50, {p2_bullet1});
    std::uint8_t p2_kills = 1;


    // p2_nombre = "Ana";
    // p2_id = 5678;
    // p2_coords.x = 155;
    // p2_coords.y = p1_coords.y - 5;
    // p2_stats = {80, 60};
    // p2_angle = 120;
    // p2_skin = GameConstants::Skins::GUERRILLA;
    // p2_team = GameConstants::Team::TERRORISTS;
    //
    // p3_nombre = "Ana222";
    // p3_id = 568;
    // p3_coords.x = p1_coords.x - 25;
    // p3_coords.y = p1_coords.y - 25;
    // p3_stats = {80, 60};
    // p3_angle = 270;
    // p3_skin = GameConstants::Skins::L337_KREW;
    // p3_team = GameConstants::Team::TERRORISTS;
    //
    PlayerInformation p1(p1_id, p1_nombre, p1_skin, p1_coords, p1_angle, p1_actualMoney,
                         p1_actualHealthPoints, p1_weaponsInfo, p1_actualWeapon, p1_kills);
    PlayerInformation p2(p2_id, p2_nombre, p2_skin, p2_coords, p2_angle, p2_actualMoney,
                         p2_actualHealthPoints, p2_weaponsInfo, p2_actualWeapon, p2_kills);
    // PlayerInformation p3_

    playerList.push_back(p1);
    playerList.push_back(p2);

    gameSnapshot.playersInfo = playerList;
    // aca seteo que tan a la izquierda se va
    // el mapa cuando arranca a renderizar
    // gameSnapshot.offset.y = 0; // TILE_HEIGHT * 4;
    // gameSnapshot.offset.x = 0; // TILE_WIDTH * 4;

    // std::vector<DroppedWeaponDTO> weaponList;
    //
    // DroppedWeaponDTO ak_1;
    // ak_1.id = WeaponConstants::AK47;
    // ak_1.pos.x = 30;
    // ak_1.pos.y = 25;
    // ak_1.angle = 0;
    // DroppedWeaponDTO ak_2;
    // ak_2.id = WeaponConstants::AK47;
    // ak_2.pos.x = 15;
    // ak_2.pos.y = 40;
    // ak_2.angle = 220;
    // DroppedWeaponDTO m3_1;
    // m3_1.id = WeaponConstants::M3;
    // m3_1.pos.x = 80;
    // m3_1.pos.y = 110;
    // m3_1.angle = 330;
    // DroppedWeaponDTO glock_1;
    // glock_1.id = WeaponConstants::GLOCK;
    // glock_1.pos.x = 300;
    // glock_1.pos.y = 10;
    // glock_1.angle = 60;
    // DroppedWeaponDTO bomb;
    // bomb.id = WeaponConstants::BOMB;
    // bomb.pos.x = 190;
    // bomb.pos.y = 130;
    // bomb.angle = 60;
    // DroppedWeaponDTO awp;
    // awp.id = WeaponConstants::AWP;
    // awp.pos.x = 130;
    // awp.pos.y = 190;
    // awp.angle = 60;
    //
    // weaponList.push_back(ak_1);
    // weaponList.push_back(m3_1);
    // weaponList.push_back(glock_1);
    // weaponList.push_back(ak_2);
    // weaponList.push_back(bomb);
    // weaponList.push_back(awp);
    //
    // gameSnapshot.game.map.droppedWeapons = weaponList;
}
