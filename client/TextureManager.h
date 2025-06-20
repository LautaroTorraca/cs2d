#pragma once
#include <cstdlib>
#include <unordered_map>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "Constants/ClientConstants.h"
#include "SDL2pp/Texture.hh"
#include "server/Constants/MapTypeConstants.h"
#include "server/Skin.h"
#include "server/WeaponConstants.h"

enum ColorKey { black, magenta, none };
using namespace SDL2pp;

class TextureManager {
private:
    Renderer& renderer;
    std::unordered_map<Skin, Texture> texturesSkins;
    std::unordered_map<MapType, Texture> texturesTiles;
    std::unordered_map<UiType, Texture> texturesUI;
    std::unordered_map<WeaponType, Texture> texturesWeapons;

    Texture fovTexture;
    Texture removeBackground(ColorKey color, std::string filename);

public:
    TextureManager(Renderer& renderer);
    Texture& getSkin(Skin id);
    Texture& getTileMap(MapType id);
    Texture& getDroppedWeapon(WeaponType id);
    Texture& getWeapon(WeaponType id);
    Texture& getUi(UiType id);
    Texture& getFov();
};
