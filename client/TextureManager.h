#pragma once
#include "Constants/ClientConstants.h"
#include "SDL2pp/Texture.hh"
// #include "client/playerDataConstants.h"
#include "server/Skin.h"
#include "server/WeaponConstants.h"
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
  std::unordered_map<Skin, Texture> texturesSkins;
  std::unordered_map<int, Texture> texturesTiles;
  std::unordered_map<int, Texture> texturesUI;
  std::unordered_map<WeaponType, Texture> texturesWeapons;

  Texture removeBackground(std::string filename);

public:
  TextureManager(Renderer &renderer);
  Texture &getSkin(Skin id);
  Texture &getTileMap(GameConstants::MapType id);
  Texture &getDroppedWeapon(WeaponType id);
  Texture &getWeapon(WeaponType id);
  Texture &getUi(Ui_type id);
};
