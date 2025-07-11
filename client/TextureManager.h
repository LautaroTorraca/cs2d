#pragma once
#include <cstdlib>
#include <unordered_map>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "Constants/ClientConstants.h"
#include "SDL2pp/Texture.hh"
#include "common/Constants/Skin.h"
#include "common/Constants/MapTypeConstants.h"

#include "EntityConstants.h"
#include "RgbValue.h"

enum ColorKey { black, magenta, none };
using namespace SDL2pp;

class TextureManager {
private:
    Renderer& renderer;
    std::unordered_map<Skin, Texture> texturesSkins;
    std::unordered_map<MapType, Texture> texturesTiles;
    std::unordered_map<UiType, Texture> texturesUI;
    std::unordered_map<EntityType, Texture> texturesWeapons;
    std::unordered_map<EntityType, Texture> texturesWeaponsHeld;
    std::unordered_map<int, Font> fontSizes;
    Texture explotionTexture;

    Texture fovTexture;
    Texture removeBackground(ColorKey color, std::string filename);

public:
    TextureManager(Renderer& renderer, double res_w, double res_h);
    Texture& getSkin(Skin id);
    Texture& getTileMap(MapType id);
    Texture& getDroppedWeapon(EntityType id);
    Texture& getWeapon(EntityType id);
    Texture& getWeaponHeld(EntityType id);
    Texture& getUi(UiType id);
    Texture& getFov();
    Texture& getExplotion();
    Texture getFont(int fontSize, std::string text, RgbValue color);
};
