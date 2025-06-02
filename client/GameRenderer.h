#pragma once
#include "SDL2pp/Texture.hh"
#include "TextureManager.h"
#include "common/Constants/PlayerDataConstants.h"
#include "common/Constants/SnapshotConstants.h"
// #include "weaponConstants.h"

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>
#include <cstddef>

using namespace SDL2pp;
using namespace DTO;
// TODO: cambiar por las resoluciones configuradas en el YAML.
// constexpr int RES_WIDTH = 640;
// constexpr int RES_HEIGTH = 400;

class GameRenderer {

private:
  Window window;
  Renderer renderer;
  TextureManager textureManager;
  std::vector<std::vector<int>> tileMap;
  size_t clientID;

  void renderMap(std::vector<std::vector<int>> tileMap, Coords offset);
  void renderUI(Stats stat, Inventory inv, Coords mouseCoords);
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

  void renderPointer(Coords mouseCoords);

public:
  GameRenderer(std::vector<std::vector<int>> tileMap, size_t clientId);
  void renderScreen(Snapshot gameSnapshot);
};
