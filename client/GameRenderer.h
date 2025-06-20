#pragma once
#include "Constants/ClientConstants.h"
#include "SDL2pp/Texture.hh"
#include "common/Constants/PlayerDataConstants.h"
#include "common/Constants/SnapshotConstants.h"
#include "server/Constants/MapTypeConstants.h"

#include "CoordinateInformation.h"
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

    void renderMap(std::vector<std::vector<uint8_t>> tileMap, MapType map);
    void renderPlayers(std::vector<PlayerInformation> players, size_t clientId);
    void renderPlayer(Texture& sprite, PlayerInformation player, int variation);
    void renderCurrentPlayer(Texture& sprite, PlayerInformation player, int variation);
    void renderFloorItems(std::vector<DropInformation> weaponList);
    void renderTile(Texture& mapTile, int mapWidth, int tile, int pos);

    void renderBomb(CoordinateInformation plantedBombPosition);
    void renderFloorWeapon(Texture& sprite, DropInformation wpn);

    void renderPointer(Coords mouseCoords);
    void renderUI(PlayerInformation& player, Snapshot gameSnapshot, Coords mouseCoords);

    int16_t renderNumberStream(CoordinateInformation pos, int number, int digits,
                               int separation = 0, int height = HUD_NUM_H, int width = HUD_NUM_W);
    int16_t renderNumber(CoordinateInformation posInScreen, int number, int height = HUD_NUM_H,
                         int width = HUD_NUM_W);
    int16_t renderSymbol(CoordinateInformation posInScreen, UiSymbol symbol);

    int16_t renderWeaponGlyph(CoordinateInformation posInScreen, WeaponType weapon);
    void renderBullets(PlayerInformation& player);

    Texture createLightCone(int radius, double angleDeg);
    void renderLightEffects(Texture& cone, double angle);
    void drawFOVStencil(const CoordinateInformation& playerCoords, double directionDeg,
                        double fovDeg, int radius);
    // void drawStencil(const Coords& playerCoords, double playerAngle, double angleDegrees);
    // void drawVisionCone(SDL2pp::Renderer& renderer, Coords origin, double directionDeg,
    //                     double fovDeg, double length);

public:
    GameRenderer(std::vector<std::vector<uint8_t>> tileMap, size_t clientId);
    void renderScreen(Snapshot gameSnapshot, MapType map, Coords mouseCoords);
};
