#include "TextureManager.h"
#include "SDL2pp/Renderer.hh"
#include "SDL2pp/Texture.hh"
// #include "client/playerDataConstants.h"
// #include "client/playerDataConstants.h"
#include "gameConstants.h"
#include "weaponConstants.h"
// #include <algorithm>
#include <string>

// #include "Surface.h"

TextureManager::TextureManager(Renderer &renderer) : renderer(renderer) {

  // terrain
  // texturesTiles.emplace(
  //     GameConstants::TERRAIN,
  //     Texture(renderer, "/home/toto/facultad/taller/tp-grupal-taller-CS2D/"
  // "client/assets/terrain/terrain.png"));
  // weapons
  texturesWeapons.emplace(
      WeaponConstants::AWP,
      removeBackground("/home/toto/facultad/taller/tp-grupal-taller-CS2D/"
                       "client/assets/weapons/awp.png"));
  texturesWeapons.emplace(
      WeaponConstants::M3,
      removeBackground("/home/toto/facultad/taller/tp-grupal-taller-CS2D/"
                       "client/assets/weapons/m3.png"));
  texturesWeapons.emplace(
      WeaponConstants::GLOCK,
      removeBackground("/home/toto/facultad/taller/tp-grupal-taller-CS2D/"
                       "client/assets/weapons/glock.png"));
  texturesWeapons.emplace(
      WeaponConstants::KNIFE,
      removeBackground("/home/toto/facultad/taller/tp-grupal-taller-CS2D/"
                       "client/assets/weapons/knife.png"));
  texturesWeapons.emplace(
      WeaponConstants::BOMB,
      removeBackground("/home/toto/facultad/taller/tp-grupal-taller-CS2D/"
                       "client/assets/weapons/bomb.png"));
  texturesWeapons.emplace(
      WeaponConstants::AK47,
      removeBackground("/home/toto/facultad/taller/tp-grupal-taller-CS2D/"
                       "client/assets/weapons/ak47.png"));

  // skins
  texturesSkins.emplace(
      GameConstants::SEAL_FORCE,
      removeBackground("/home/toto/facultad/taller/tp-grupal-taller-CS2D/"
                       "client/assets/skins/CT/ct-2.png"));
  texturesSkins.emplace(
      GameConstants::FRENCH_GIGN,
      removeBackground("/home/toto/facultad/taller/tp-grupal-taller-CS2D/"
                       "client/assets/skins/CT/ct-3.png"));
  texturesSkins.emplace(
      GameConstants::UK_SAS,
      removeBackground("/home/toto/facultad/taller/tp-grupal-taller-CS2D/"
                       "client/assets/skins/CT/ct-1.png"));
  texturesSkins.emplace(
      GameConstants::GERMAN_GSG9,
      removeBackground("/home/toto/facultad/taller/tp-grupal-taller-CS2D/"
                       "client/assets/skins/CT/ct-4.png"));
  texturesSkins.emplace(
      GameConstants::L337_KREW,
      removeBackground("/home/toto/facultad/taller/tp-grupal-taller-CS2D/"
                       "client/assets/skins/TT/tt-2.png"));
  texturesSkins.emplace(
      GameConstants::ARCTIC_AVENGER,
      removeBackground("/home/toto/facultad/taller/tp-grupal-taller-CS2D/"
                       "client/assets/skins/TT/tt-3.png"));
  texturesSkins.emplace(
      GameConstants::PHOENIX,
      removeBackground("/home/toto/facultad/taller/tp-grupal-taller-CS2D/"
                       "client/assets/skins/TT/tt-1.png"));
  texturesSkins.emplace(
      GameConstants::GUERRILLA,
      removeBackground("/home/toto/facultad/taller/tp-grupal-taller-CS2D/"
                       "client/assets/skins/TT/tt-4.png"));
  // maps
  texturesTiles.emplace(
      GameConstants::DUST,
      Texture(renderer, "/home/toto/facultad/taller/tp-grupal-taller-CS2D/"
                        "client/assets/tilemaps/dust.png"));
}

Texture &TextureManager::getSkin(GameConstants::Skins id) {
  return texturesSkins.at(id);
}
Texture &TextureManager::getTileMap(GameConstants::MapType id) {
  return texturesTiles.at(id);
}

Texture &TextureManager::getDroppedWeapon(WeaponConstants::WeaponId id) {
  return texturesWeapons.at(id);
}

Texture &TextureManager::getWeapon(WeaponConstants::WeaponId id) {
  return texturesWeapons.at(id);
}

Texture TextureManager::removeBackground(std::string filename) {

  Surface sf(filename);

  sf.SetColorKey(true, SDL_MapRGB(sf.Get()->format, 0xFF, 0x00, 0xFF));

  Texture tx(renderer, sf);

  return tx;
}
