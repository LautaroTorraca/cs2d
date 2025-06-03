#include "TextureManager.h"
#include "SDL2pp/Renderer.hh"
#include "SDL2pp/Texture.hh"
// #include "client/playerDataConstants.h"
// #include "client/playerDataConstants.h"
#include "Constants/ClientConstants.h"
#include "gameConstants.h"
#include "weaponConstants.h"
// #include <algorithm>
#include <string>

// #include "Surface.h"

#include "server/Skin.h"
#include "server/Team.h"

TextureManager::TextureManager(Renderer &renderer) : renderer(renderer) {

  // UI
  texturesUI.emplace(Ui_type::NumsUI,
                     Texture(renderer,
                             "/home/toto/facultad/taller/tp-grupal-taller-CS2D/"
                             "client/assets/ui/hud_nums.png"));
  texturesUI.emplace(Ui_type::SymbUI,
                     Texture(renderer,
                             "/home/toto/facultad/taller/tp-grupal-taller-CS2D/"
                             "client/assets/ui/hud_symbols.png"));
  texturesUI.emplace(Ui_type::CursorUI,
                     Texture(renderer,
                             "/home/toto/facultad/taller/tp-grupal-taller-CS2D/"
                             "client/assets/ui/pointer.png"));

  // weapons
  texturesWeapons.emplace(
      WeaponType::AWP,
      removeBackground("/home/toto/facultad/taller/tp-grupal-taller-CS2D/"
                       "client/assets/weapons/awp.png"));
  texturesWeapons.emplace(
      WeaponType::M3,
      removeBackground("/home/toto/facultad/taller/tp-grupal-taller-CS2D/"
                       "client/assets/weapons/m3.png"));
  texturesWeapons.emplace(
      WeaponType::GLOCK,
      removeBackground("/home/toto/facultad/taller/tp-grupal-taller-CS2D/"
                       "client/assets/weapons/glock.png"));
  texturesWeapons.emplace(
      WeaponType::KNIFE,
      removeBackground("/home/toto/facultad/taller/tp-grupal-taller-CS2D/"
                       "client/assets/weapons/knife.png"));
  texturesWeapons.emplace(
      WeaponType::BOMB,
      removeBackground("/home/toto/facultad/taller/tp-grupal-taller-CS2D/"
                       "client/assets/weapons/bomb.png"));
  texturesWeapons.emplace(
      WeaponType::AK47,
      removeBackground("/home/toto/facultad/taller/tp-grupal-taller-CS2D/"
                       "client/assets/weapons/ak47.png"));

  // skins
  texturesSkins.emplace(
      Skin::SEAL_FORCE,
      removeBackground("/home/toto/facultad/taller/tp-grupal-taller-CS2D/"
                       "client/assets/skins/CT/ct-2.png"));
  texturesSkins.emplace(
      Skin::FRENCH_GIGN,
      removeBackground("/home/toto/facultad/taller/tp-grupal-taller-CS2D/"
                       "client/assets/skins/CT/ct-3.png"));
  texturesSkins.emplace(
      Skin::UK_SAS,
      removeBackground("/home/toto/facultad/taller/tp-grupal-taller-CS2D/"
                       "client/assets/skins/CT/ct-1.png"));
  texturesSkins.emplace(
      Skin::GERMAN_GSG9,
      removeBackground("/home/toto/facultad/taller/tp-grupal-taller-CS2D/"
                       "client/assets/skins/CT/ct-4.png"));
  texturesSkins.emplace(
      Skin::L337_KREW,
      removeBackground("/home/toto/facultad/taller/tp-grupal-taller-CS2D/"
                       "client/assets/skins/TT/tt-2.png"));
  texturesSkins.emplace(
      Skin::ARCTIC_AVENGER,
      removeBackground("/home/toto/facultad/taller/tp-grupal-taller-CS2D/"
                       "client/assets/skins/TT/tt-3.png"));
  texturesSkins.emplace(
      Skin::PHOENIX,
      removeBackground("/home/toto/facultad/taller/tp-grupal-taller-CS2D/"
                       "client/assets/skins/TT/tt-1.png"));
  texturesSkins.emplace(
      Skin::GUERRILLA,
      removeBackground("/home/toto/facultad/taller/tp-grupal-taller-CS2D/"
                       "client/assets/skins/TT/tt-4.png"));
  // maps
  texturesTiles.emplace(
      GameConstants::DUST,
      Texture(renderer, "/home/toto/facultad/taller/tp-grupal-taller-CS2D/"
                        "client/assets/tilemaps/dust.png"));
}

Texture &TextureManager::getSkin(Skin id) {
  return texturesSkins.at(id);
}
Texture &TextureManager::getTileMap(GameConstants::MapType id) {
  return texturesTiles.at(id);
}

Texture &TextureManager::getDroppedWeapon(WeaponType id) {
  return texturesWeapons.at(id);
}

Texture &TextureManager::getWeapon(WeaponType id) {
  return texturesWeapons.at(id);
}

Texture &TextureManager::getUi(Ui_type id) { return texturesUI.at(id); }

Texture TextureManager::removeBackground(std::string filename) {

  Surface sf(filename);

  sf.SetColorKey(true, SDL_MapRGB(sf.Get()->format, 0xFF, 0x00, 0xFF));

  Texture tx(renderer, sf);

  return tx;
}
