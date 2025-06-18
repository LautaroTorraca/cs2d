#include "TextureManager.h"

#include <string>

#include "Constants/ClientConstants.h"
#include "SDL2pp/Renderer.hh"
#include "SDL2pp/Texture.hh"
#include "server/Constants/MapTypeConstants.h"
#include "server/Skin.h"

TextureManager::TextureManager(Renderer& renderer):
        renderer(renderer),
        fovTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, RES_WIDTH,
                   RES_HEIGTH) {

    // UI
    texturesUI.emplace(UiType::NumsUI, removeBackground(black, "../client/assets/ui/hud_nums.png"));
    texturesUI.emplace(UiType::SymbUI,
                       removeBackground(black, "../client/assets/ui/hud_symbols.png"));
    texturesUI.emplace(UiType::CursorUI,
                       removeBackground(magenta, "../client/assets/ui/pointer.png"));

    // weapons
    texturesWeapons.emplace(WeaponType::AWP,
                            removeBackground(magenta, "../client/assets/weapons/awp.png"));
    texturesWeapons.emplace(WeaponType::M3,
                            removeBackground(magenta, "../client/assets/weapons/m3.png"));
    texturesWeapons.emplace(WeaponType::GLOCK,
                            removeBackground(magenta, "../client/assets/weapons/glock.png"));
    texturesWeapons.emplace(WeaponType::KNIFE,
                            removeBackground(magenta, "../client/assets/weapons/knife.png"));
    texturesWeapons.emplace(WeaponType::BOMB,
                            removeBackground(magenta, "../client/assets/weapons/bomb.png"));
    texturesWeapons.emplace(WeaponType::AK47,
                            removeBackground(magenta, "../client/assets/weapons/ak47.png"));

    // skins
    texturesSkins.emplace(Skin::SEAL_FORCE,
                          removeBackground(magenta, "../client/assets/skins/CT/ct-2.png"));
    texturesSkins.emplace(Skin::FRENCH_GIGN,
                          removeBackground(magenta, "../client/assets/skins/CT/ct-3.png"));
    texturesSkins.emplace(Skin::UK_SAS,
                          removeBackground(magenta, "../client/assets/skins/CT/ct-1.png"));
    texturesSkins.emplace(Skin::GERMAN_GSG9,
                          removeBackground(magenta, "../client/assets/skins/CT/ct-4.png"));
    texturesSkins.emplace(Skin::L337_KREW,
                          removeBackground(magenta, "../client/assets/skins/TT/tt-2.png"));
    texturesSkins.emplace(Skin::ARCTIC_AVENGER,
                          removeBackground(magenta, "../client/assets/skins/TT/tt-3.png"));
    texturesSkins.emplace(Skin::PHOENIX,
                          removeBackground(magenta, "../client/assets/skins/TT/tt-1.png"));
    texturesSkins.emplace(Skin::GUERRILLA,
                          removeBackground(magenta, "../client/assets/skins/TT/tt-4.png"));
    // maps
    texturesTiles.emplace(MapType::DUST, Texture(renderer, "../client/assets/tilemaps/dust.png"));

    fovTexture.SetBlendMode(SDL_BLENDMODE_BLEND);
    // fovTexture = Texture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 640, 400);
}

Texture& TextureManager::getSkin(Skin id) { return texturesSkins.at(id); }
Texture& TextureManager::getTileMap(MapType id) {
    return texturesTiles.at(id);
}

Texture& TextureManager::getDroppedWeapon(WeaponType id) { return texturesWeapons.at(id); }

Texture& TextureManager::getWeapon(WeaponType id) { return texturesWeapons.at(id); }

Texture& TextureManager::getUi(UiType id) { return texturesUI.at(id); }

Texture& TextureManager::getFov() { return fovTexture; }

Texture TextureManager::removeBackground(ColorKey colorKey, std::string filename) {

    Surface sf(filename);

    switch (colorKey) {

        case magenta:
            sf.SetColorKey(true, SDL_MapRGB(sf.Get()->format, 0xFF, 0x00, 0xFF));
            break;
        case black:
            sf.SetColorKey(true, SDL_MapRGB(sf.Get()->format, 0x00, 0x00, 0x00));
            break;
        case none:
            break;
    }

    Texture tx(renderer, sf);

    return tx;
}
