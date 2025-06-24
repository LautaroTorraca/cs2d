#pragma once
#include "Constants/ClientConstants.h"
#include "SDL2pp/Texture.hh"
#include "common/Constants/PlayerDataConstants.h"
#include "common/Constants/SnapshotConstants.h"
#include "server/Constants/MapTypeConstants.h"
#include "server/GameStatus.h"

#include "CoordinateInformation.h"
#include "EntityConstants.h"
#include "ExplotionSprite.h"
#include "PlayerInformation.h"
#include "PlayerSprite.h"
#include "RgbValue.h"
#include "SoundManager.h"
#include "TextureManager.h"
// #include "weaponConstants.h"

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

using namespace SDL2pp;
using namespace DTO;

class GameRenderer {

private:
    double resolution_width;
    double resolution_heigth;
    Window window;
    Renderer renderer;
    TextureManager textureManager;
    std::vector<std::vector<uint8_t>> tileMap;
    size_t clientID;
    CoordinateInformation offset;
    int playerFrame = 0;
    ExplotionSprite explotion;
    bool roundBombExploded = false;
    GameStatus prevStatus;
    SoundManager soundManager;
    std::map<ProductType, double> shopInfo;

    std::unordered_map<size_t, PlayerSprite> playerSprites;

    void renderMap(std::vector<std::vector<uint8_t>> tileMap, MapType map);
    void renderPlayers(std::vector<PlayerInformation> players);
    void renderPlayer(Texture& sprite, PlayerInformation player, int variation);
    void renderCurrentPlayer(Texture& sprite, PlayerInformation player, int variation);
    void renderFloorItems(std::vector<DropInformation> weaponList);
    void renderTile(Texture& mapTile, int mapWidth, int tile, int pos);

    void renderBomb(CoordinateInformation plantedBombPosition, GameStatus status);
    void renderFloorWeapon(Texture& sprite, DropInformation wpn);

    void renderPointer(Coords mouseCoords);
    void renderUI(PlayerInformation& player, Snapshot gameSnapshot, Coords mouseCoords);

    int16_t renderNumberStream(CoordinateInformation pos, int number, int digits, int separation,
                               RgbValue color, int height = HUD_NUM_H, int width = HUD_NUM_W);
    int16_t renderNumber(CoordinateInformation posInScreen, int number, RgbValue color,
                         int height = HUD_NUM_H, int width = HUD_NUM_W);
    int16_t renderSymbol(CoordinateInformation posInScreen, UiSymbol symbol, RgbValue color);

    int16_t renderWeaponGlyph(CoordinateInformation posInScreen, EntityType weapon, RgbValue color,
                              double mult = 1);
    void renderBullets(PlayerInformation& player);
    void renderHeldWeapon(PlayerInformation& player);

    Texture createLightCone(int radius, double angleDeg);
    void renderLightEffects(Texture& cone, double angle);
    void drawFOVStencil(const CoordinateInformation& playerCoords, double directionDeg,
                        double fovDeg, int radius);
    void renderText(std::string text, CoordinateInformation pos, int fontSize, RgbValue color);
    void renderBuyButton(CoordinateInformation pos, int button, int price);
    void setRoundWinMenu(GameStatus state);
    void setLeaderBoard(const std::vector<PlayerInformation>& players, uint8_t ct_rounds,
                        uint8_t tt_rounds);
    void stateSounds(GameStatus state);
    PlayerInformation& fillPlayerStatesAndFindClient(Snapshot& snapshot);

public:
    GameRenderer(std::vector<std::vector<uint8_t>> tileMap, size_t clientId, double width,
                 double height, std::map<ProductType, double> shopInfo);

    bool setScreen(Snapshot gameSnapshot, MapType map, Coords mouseCoords);
    void setBuyMenu();
    void render();
};
