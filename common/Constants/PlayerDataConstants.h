#pragma once
#include <cstdint>
//
// #include "gameConstants.h"
// #include "weaponConstants.h"
// #include <cstddef>
// #include <cstdint>
// #include <string>
// #include <vector>
//
namespace DTO {
//
// struct DirectionDTO {
//   GameConstants::Direction direction;
// };
//
// // Estructura de coordenadas
struct Coords {
    int16_t x;
    int16_t y;
};
}  // namespace DTO
//
// // Estructura de estadísticas básicas del jugador
// struct Stats {
//   int32_t money;
//   int16_t life;
// };
//
// // Estructura de cuchillo
// struct Knife {
//   bool hasKnife;
//   bool equipped;
// };
//
// // Estructura de arma principal
// struct PrimaryWeaponDTO {
//   WeaponConstants::WeaponId weapon;
//   int16_t ammo;
//   bool equipped;
// };
//
// // Estructura de arma secundaria
// struct SecondaryWeaponDTO {
//   WeaponConstants::WeaponId weapon;
//   int16_t ammo;
//   bool equipped;
// };
//
// struct DroppedWeaponDTO {
//   WeaponConstants::WeaponId id;
//   Coords pos;
//   double angle;
// };
//
// // Estructura de inventario
// struct Inventory {
//   Knife knife;
//   PrimaryWeaponDTO primaryWeapon;
//   SecondaryWeaponDTO secondaryWeapon;
//   bool bomb;
// };
//
// // Estructura de datos del jugador
// struct PlayerData {
//   std::string nombre;
//   size_t id;
//   Coords coords;
//   Inventory inventory;
//   Stats stats;
//   double angle;
//   GameConstants::Skins skin;
//   GameConstants::Team team;
// };
//
// // Mapa
// struct GameMap {
//   std::vector<DroppedWeaponDTO> droppedWeapons;
// };
//
// // Estructura de juego
// struct Game {
//   // int playersCount;
//   // std::string gameName;
//   GameMap map;
//   std::vector<PlayerData> players;
// };
//
// // Estructura de lista de juegos
// struct GameList {
//   std::vector<std::string> games;
// };
//
// // Estructura para unirse a un juego
// struct JoinDTO {
//   PlayerData player;
//   std::string gameName;
// };
//
// // XXX: organizar el pre snapshot con la confugracion del mapa, spawnpoints,
// // etc....
// // - tileMap
// // - tu_id puede ser
// } // namespace DTO
