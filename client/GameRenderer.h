#pragma once
#include "SDL2pp/Texture.hh"
#include "TextureManager.h"
#include "playerDataConstants.h"
// #include "weaponConstants.h"

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

using namespace SDL2pp;
using namespace DTO;
// TODO: cambiar por las resoluciones configuradas en el YAML.
// constexpr int RES_WIDTH = 640;
// constexpr int RES_HEIGTH = 400;

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

class GameRenderer {

private:
  Window window;
  Renderer renderer;
  TextureManager textureManager;

  void renderMap(std::vector<std::vector<int>> tileMap, Coords offset);
  void renderPlayers(std::vector<PlayerData> players, Coords offset,
                     size_t clientId);
  void renderPlayer(Texture &sprite, PlayerData player, int variation,
                    Coords offset);
  void renderCurrentPlayer(Texture &sprite, PlayerData player, int variation,
                           Coords offset);
  void renderFloorItems(std::vector<DroppedWeaponDTO> weaponList,
                        Coords offset);
  void renderTile(Texture &mapTile, int tile, int pos, Coords offset);

  void renderFloorWeapon(Texture &sprite, DroppedWeaponDTO wpn, Coords offset);
  void renderPlayersAsCubes(std::vector<PlayerData> players);

public:
  GameRenderer();
  void renderScreen(snapshot gameSnapshot);
};
