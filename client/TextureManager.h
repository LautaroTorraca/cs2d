#pragma once
#include "SDL2pp/Texture.hh"
// #include "client/playerDataConstants.h"
#include "gameConstants.h"
#include "weaponConstants.h"
// #include "playerDataConstants.h"
#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>
#include <cstdlib>
// #include <string>
#include <unordered_map>

using namespace SDL2pp;
// using namespace DTO;

class TextureManager {
private:
  Renderer &renderer;
  std::unordered_map<GameConstants::Skins, Texture> texturesSkins;
  std::unordered_map<int, Texture> texturesTiles;
  std::unordered_map<int, Texture> texturesWeapons;

  Texture removeBackground(std::string filename);

public:
  TextureManager(Renderer &renderer);
  Texture &getSkin(GameConstants::Skins id);
  Texture &getTileMap(GameConstants::MapType id);
  Texture &getDroppedWeapon(WeaponConstants::WeaponId id);
  Texture &getWeapon(WeaponConstants::WeaponId id);
};
