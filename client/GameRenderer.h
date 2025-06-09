#pragma once
#include "SDL2pp/Texture.hh"
#include "common/Constants/PlayerDataConstants.h"
#include "common/Constants/SnapshotConstants.h"
#include "server/Constants/MapTypeConstants.h"

#include "PlayerInformation.h"
#include "TextureManager.h"
// #include "weaponConstants.h"

#include <cstddef>
#include <cstdint>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

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
    std::vector<std::vector<uint8_t>> tileMap;
    size_t clientID;
    Coords offset;

    void renderMap(std::vector<std::vector<uint8_t>> tileMap, MapType map, Coords offset);
    void renderPlayers(std::vector<PlayerInformation> players, Coords offset, size_t clientId);
    void renderPlayer(Texture& sprite, PlayerInformation player, int variation, Coords offset);
    void renderCurrentPlayer(Texture& sprite, PlayerInformation player, int variation,
                             Coords offset);
    void renderFloorItems(std::vector<DropInformation> weaponList, Coords offset);
    void renderTile(Texture& mapTile, int tile, int pos, Coords offset);

    void renderFloorWeapon(Texture& sprite, DropInformation wpn, Coords offset);

    void renderPointer(Coords mouseCoords);
    void renderUI(PlayerInformation& player, Snapshot gameSnapshot, Coords mouseCoords);

    int16_t renderNumber(Coords posInScreen, int number);
    int16_t renderSymbol(Coords posInScreen, UiSymbol symbol);

    int16_t renderWeaponGlyph(Coords posInScreen, WeaponType weapon);
    void renderBullets(PlayerInformation& player);

public:
    GameRenderer(std::vector<std::vector<uint8_t>> tileMap, size_t clientId);
    void renderScreen(Snapshot gameSnapshot, MapType map, Coords mouseCoords);
};
