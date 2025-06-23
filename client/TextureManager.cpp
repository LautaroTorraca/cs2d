#include "TextureManager.h"

#include <string>

#include "Constants/ClientConstants.h"
#include "SDL2pp/Renderer.hh"
#include "SDL2pp/Texture.hh"
#include "server/Constants/MapTypeConstants.h"

#include "SDL_ttf.h"
// #include "server/ProductType.h"
#include "server/Skin.h"

// #include "Explotion.h"
#include "EntityConstants.h"
#include "RgbValue.h"

TextureManager::TextureManager(Renderer& renderer):
        renderer(renderer),
        fovTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, RES_WIDTH,
                   RES_HEIGTH),

        explotionTexture(removeBackground(none, "../client/assets/explosion.png")) {

    if (TTF_Init() == -1) {
        throw std::runtime_error("error ttf_init()" + std::string(TTF_GetError()));
    }

    // FONTS
    fontSizes.emplace(20, (TTF_OpenFont("../client/assets/text/sourcesans.ttf", 20)));
    fontSizes.emplace(18, (TTF_OpenFont("../client/assets/text/sourcesans.ttf", 18)));
    fontSizes.emplace(15, (TTF_OpenFont("../client/assets/text/sourcesans.ttf", 15)));

    // AMMO
    texturesWeapons.emplace(EntityType::P_AMMO,
                            removeBackground(black, "../client/assets/primaryammo.png"));
    texturesWeapons.emplace(EntityType::S_AMMO,
                            removeBackground(black, "../client/assets/secondaryammo.png"));


    // UI
    texturesUI.emplace(UiType::NumsUI, removeBackground(black, "../client/assets/ui/hud_nums.png"));
    texturesUI.emplace(UiType::SymbUI,
                       removeBackground(black, "../client/assets/ui/hud_symbols.png"));
    texturesUI.emplace(UiType::CursorUI,
                       removeBackground(magenta, "../client/assets/ui/pointer.png"));

    // weapons held
    texturesWeaponsHeld.emplace(EntityType::AWP,
                                removeBackground(black, "../client/assets/weapons/awp_h.png"));
    texturesWeaponsHeld.emplace(EntityType::M3,
                                removeBackground(black, "../client/assets/weapons/m3_h.png"));
    texturesWeaponsHeld.emplace(EntityType::GLOCK,
                                removeBackground(black, "../client/assets/weapons/glock_h.png"));
    texturesWeaponsHeld.emplace(EntityType::KNIFE,
                                removeBackground(magenta, "../client/assets/weapons/knife_h.png"));
    texturesWeaponsHeld.emplace(EntityType::AK47,
                                removeBackground(black, "../client/assets/weapons/ak47_h.png"));
    texturesWeaponsHeld.emplace(EntityType::BOMB,
                                removeBackground(magenta, "../client/assets/weapons/bomb_h.png"));

    // weapons
    texturesWeapons.emplace(EntityType::AWP,
                            removeBackground(magenta, "../client/assets/weapons/awp.png"));
    texturesWeapons.emplace(EntityType::M3,
                            removeBackground(magenta, "../client/assets/weapons/m3.png"));
    texturesWeapons.emplace(EntityType::GLOCK,
                            removeBackground(magenta, "../client/assets/weapons/glock.png"));
    texturesWeapons.emplace(EntityType::KNIFE,
                            removeBackground(magenta, "../client/assets/weapons/knife.png"));
    texturesWeapons.emplace(EntityType::BOMB,
                            removeBackground(black, "../client/assets/weapons/bomb.png"));
    texturesWeapons.emplace(EntityType::AK47,
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
    texturesTiles.emplace(MapType::AZTEC_VILLAGE,
                          Texture(renderer, "../client/assets/tilemaps/aztec.png"));
    texturesTiles.emplace(MapType::TRAINING_ZONE,
                          Texture(renderer, "../client/assets/tilemaps/inferno.png"));

    fovTexture.SetBlendMode(SDL_BLENDMODE_BLEND);
    // fovTexture = Texture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 640,
    // 400);
}

Texture& TextureManager::getSkin(Skin id) { return texturesSkins.at(id); }
Texture& TextureManager::getTileMap(MapType id) { return texturesTiles.at(id); }

Texture& TextureManager::getDroppedWeapon(EntityType id) { return texturesWeapons.at(id); }

Texture& TextureManager::getWeapon(EntityType id) { return texturesWeapons.at(id); }

Texture& TextureManager::getWeaponHeld(EntityType id) { return texturesWeaponsHeld.at(id); }

Texture& TextureManager::getUi(UiType id) { return texturesUI.at(id); }

Texture& TextureManager::getFov() { return fovTexture; }

Texture& TextureManager::getExplotion() { return explotionTexture; }

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

Texture TextureManager::getFont(int fontSize, std::string text, RgbValue color) {

    if (!fontSizes.contains(fontSize)) {
        fontSizes.emplace(fontSize,
                          (TTF_OpenFont("../client/assets/text/sourcesans.ttf", fontSize)));
    }
    Font& font = fontSizes.at(fontSize);
    Surface textSurface(font.RenderText_Solid(text.c_str(), {color.r, color.g, color.b, color.a}));
    Texture textTexture(renderer, textSurface);
    return textTexture;
}
