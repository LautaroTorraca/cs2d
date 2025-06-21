#include "GameRenderer.h"

#include <cstdint>
#include <iostream>
#include <string>

#include "Constants/ClientConstants.h"
#include "Constants/PlayerDataConstants.h"
#include "SDL2pp/Optional.hh"
#include "SDL2pp/Texture.hh"
// #include "build/_deps/sdl2_ttf-src/SDL_ttf.h"
#include "server/Constants/MapTypeConstants.h"
#include "server/WeaponConstants.h"

#include "CoordinateInformation.h"
// #include "Explotion.h"
#include "Explotion.h"
#include "PlayerInformation.h"
#include "ProjectileInformation.h"
#include "RgbValue.h"
#include "SDL2_gfxPrimitives.h"
#include "SDL_blendmode.h"
#include "SDL_render.h"
#include "SDL_stdinc.h"
#include "SnapshotConstants.h"
#include "TextureManager.h"


GameRenderer::GameRenderer(std::vector<std::vector<uint8_t>> tileMap, size_t clientId):
        window("CS-Go 2D???", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, RES_WIDTH,
               RES_HEIGTH, 0),
        renderer(window, -1, SDL_RENDERER_ACCELERATED),
        textureManager(renderer),
        tileMap(tileMap),
        clientID(clientId),
        explotion(renderer, textureManager.getExplotion()) {}

void GameRenderer::setScreen(Snapshot gameSnapshot, MapType map, Coords mouseCoords) {

    float xScale = (float(RES_WIDTH) / RES_WIDTH_BASE);
    float yScale = (float(RES_HEIGTH) / RES_HEIGTH_BASE);
    renderer.SetScale(xScale, yScale);

    // TODO: cambiar por un map la lista de players.
    size_t index = 0;
    for (PlayerInformation player: gameSnapshot.playersInfo) {
        if (player.id == clientID) {
            break;
        }
        index++;
    }
    PlayerInformation& currentPlayer = gameSnapshot.playersInfo.at(index);

    srand(time(nullptr));
    int numero = rand() % 6;
    if (numero == 3) {
        std::cout << "player: " << currentPlayer.name << "\n";
    }

    offset.x = (gameSnapshot.playersInfo.at(index).position.x) - int(RES_WIDTH_BASE / 2);
    offset.y = (gameSnapshot.playersInfo.at(index).position.y) - int(RES_HEIGTH_BASE / 2);

    renderMap(tileMap, map);
    renderFloorItems(gameSnapshot.dropsInfo);
    renderBomb(gameSnapshot.plantedBombPosition);
    renderPlayers(gameSnapshot.playersInfo, clientID);
    drawFOVStencil(currentPlayer.position, currentPlayer.angle, 60, 50);
    renderUI(gameSnapshot.playersInfo.at(index), gameSnapshot, mouseCoords);
    // renderer.Present();
}

void GameRenderer::renderMap(std::vector<std::vector<uint8_t>> tileMap, MapType map) {

    Texture& tileMapTexture = textureManager.getTileMap(map);

    int posCounter = 0;
    int mapWidth = tileMap[0].size();
    for (std::vector<uint8_t> tileRow: tileMap) {
        for (int tile: tileRow) {
            renderTile(tileMapTexture, mapWidth, tile, posCounter);
            posCounter++;
        }
    }
}

void GameRenderer::renderBomb(CoordinateInformation pos) {
    if (pos.x == -1) {
        return;
    }
    Texture& sprite = textureManager.getWeapon(WeaponType::BOMB);
    CoordinateInformation off(offset.x + 25, offset.y + 5);

    // explotion.draw({pos.x - offset.x, pos.y - offset.y});

    renderer.Copy(sprite, NullOpt, Rect(pos.x - off.x, pos.y - off.y, PLAYER_WIDTH, PLAYER_HEIGTH));
}

void GameRenderer::renderPlayers(std::vector<PlayerInformation> players, size_t clientId) {

    for (PlayerInformation player: players) {
        Texture& skin = textureManager.getSkin(player.skin);
        if (player.actualWeapon.weaponType == WeaponType::KNIFE ||
            player.actualWeapon.weaponType == WeaponType::BOMB) {
            playerFrame = 1;
        } else {
            playerFrame = 3;
        }
        renderPlayer(skin, player, playerFrame);
        renderBullets(player);
        renderHeldWeapon(player);
    }
}

void GameRenderer::renderPlayer(Texture& sprite, PlayerInformation player, int variation) {

    int posSrcX = TILE_SRC_SIZE * (variation % 2);
    int div = (variation / 2);
    int posSrcY = TILE_SRC_SIZE * div;

    int offsetX = PLAYER_WIDTH / 2.0;
    int offsetY = PLAYER_HEIGTH / 2.0;
    int posPlayerX = player.position.x - offset.x - offsetX;
    int posPlayerY = player.position.y - offset.y - offsetY;

    renderer.Copy(sprite, Rect(posSrcX, posSrcY, TILE_SRC_SIZE, TILE_SRC_SIZE),
                  Rect(posPlayerX, posPlayerY, PLAYER_WIDTH, PLAYER_HEIGTH), player.angle);
}


// DEPRECATED
void GameRenderer::renderCurrentPlayer(Texture& sprite, PlayerInformation player, int variation) {

    int posX = TILE_SRC_SIZE * (variation % 2);
    int div = (variation / 2);
    int posY = TILE_SRC_SIZE * div;

    int offsetX = PLAYER_WIDTH / 2;
    int offsetY = PLAYER_HEIGTH / 2;
    // offset.x = offset.x;

    // renderer.Copy(sprite, Rect(posX, posY, TILE_SRC_SIZE, TILE_SRC_SIZE),
    //               Rect(RES_WIDTH_BASE / 2 - offsetX, RES_HEIGTH_BASE / 2 - offsetY, PLAYER_WIDTH,
    //                    PLAYER_HEIGTH),
    //               player.angle);
}

void GameRenderer::renderHeldWeapon(PlayerInformation& player) {

    // TODO: aniamcion de caminar.
    //  if (player.actualWeapon.weaponType == WeaponType::KNIFE ||
    //      player.actualWeapon.weaponType == WeaponType::BOMB) {
    //      return;
    //  }

    Texture& sprite = textureManager.getWeaponHeld(player.actualWeapon.weaponType);

    int offsetX = PLAYER_WIDTH / 2.0;
    int offsetY = PLAYER_HEIGTH / 2.0;

    int posPlayerX = player.position.x - offset.x - offsetX + 2;
    int posPlayerY = player.position.y - offset.y - offsetY - 5;

    Point rotationPoint(16 - 2, 16 + 5);
    renderer.Copy(sprite, NullOpt, Rect(posPlayerX, posPlayerY, PLAYER_WIDTH, PLAYER_HEIGTH),
                  player.angle, rotationPoint);
}
void GameRenderer::renderBullets(PlayerInformation& player) {

    for (ProjectileInformation bullet: player.actualWeapon.projectilesInfo) {

        double dx = bullet.projectilePosition.x - player.position.x;
        double dy = bullet.projectilePosition.y - player.position.y;

        double angleInRads = atan2(dy, dx);
        double angleInDegree = 180.0 * angleInRads / M_PI;
        angleInDegree += 90;
        renderer.SetDrawColor(255, 255, 0, 0);
        renderer.DrawLine(player.position.x - offset.x, player.position.y - offset.y,
                          bullet.projectilePosition.x - offset.x,
                          bullet.projectilePosition.y - offset.y);
        renderer.SetDrawColor(0, 0, 0, 255);
    }
}
void GameRenderer::renderTile(Texture& mapTile, int mapWidth, int tile, int pos) {

    int textureX = TILE_SRC_SIZE * (tile % 5);
    int div = (tile / 5);
    int textureY = TILE_SRC_SIZE * div;

    int posX = TILE_WIDTH * (pos % mapWidth);
    int div2 = (pos / mapWidth);
    int posY = TILE_HEIGHT * div2;

    renderer.Copy(mapTile, Rect(textureX, textureY, TILE_SRC_SIZE, TILE_SRC_SIZE),
                  Rect(posX - offset.x, posY - offset.y, TILE_WIDTH, TILE_HEIGHT));
}

void GameRenderer::renderFloorItems(std::vector<DropInformation> weaponList) {

    for (DropInformation item: weaponList) {
        Texture& wpnSprite = textureManager.getDroppedWeapon(item.weapon.weaponType);
        renderFloorWeapon(wpnSprite, item);
    }
}

void GameRenderer::renderFloorWeapon(Texture& sprite, DropInformation wpn) {
    renderer.Copy(sprite, NullOpt,
                  Rect(wpn.position.x - offset.x, wpn.position.y - offset.y,
                       sprite.GetWidth() * WPN_SZ_MULT, sprite.GetHeight() * WPN_SZ_MULT));
}

void GameRenderer::renderUI(PlayerInformation& player, Snapshot gameSnapshot, Coords mouseCoords) {

    RgbValue green(0, 255, 0);
    RgbValue blue(48, 69, 86);
    RgbValue orange(141, 93, 35);

    renderPointer(mouseCoords);

    if (gameSnapshot.status == BUY_TIME) {
        renderSymbol({RES_WIDTH_BASE - HUD_NUM_H, RES_HEIGTH_BASE - HUD_NUM_H * 4 - 10},
                     UiSymbol::BUY, green);
    }

    // health
    double lastPosX = 0;
    lastPosX = renderSymbol({5, RES_HEIGTH_BASE - 5}, UiSymbol::HEALTH, green);
    lastPosX = renderNumberStream({lastPosX, RES_HEIGTH_BASE - 5}, player.actualHealthPoints, 3, 2,
                                  green);

    // bullets
    lastPosX = RES_WIDTH_BASE - (HUD_NUM_W * 4) + 4;
    renderWeaponGlyph({lastPosX, RES_HEIGTH_BASE - HUD_NUM_H}, player.actualWeapon.weaponType,
                      green);
    renderNumberStream({(lastPosX + 5), RES_HEIGTH_BASE - 5}, player.actualWeapon.ammoAmount, 3, 2,
                       green);

    //  money
    lastPosX = RES_WIDTH_BASE - (HUD_NUM_W * 7);
    lastPosX = renderSymbol({lastPosX, RES_HEIGTH_BASE - HUD_NUM_H - 10}, UiSymbol::MONEY, green);
    lastPosX = renderNumberStream({(lastPosX), RES_HEIGTH_BASE - HUD_NUM_H - 10},
                                  player.actualMoney, 5, 2, green);
    // time left to defuse

    // game time
    int timerMin = gameSnapshot.actualTime / 60;
    int timerSeg = int(gameSnapshot.actualTime) % 60;

    int midScrX = RES_WIDTH_BASE / 2;
    int midScrY = RES_HEIGTH_BASE / 2;
    double timerHeigthSize = int(HUD_NUM_H / 2);
    double timerWidthSize = int(HUD_NUM_W / 2);

    lastPosX = renderNumberStream({midScrX - (2 * timerWidthSize), (timerHeigthSize + 5)}, timerMin,
                                  2, 2, green, timerHeigthSize, timerWidthSize);
    lastPosX = renderNumber({(lastPosX + 1), (timerHeigthSize + 5)}, 10, green, timerHeigthSize,
                            timerWidthSize);
    lastPosX = renderNumberStream({(lastPosX - 5), (timerHeigthSize + 5)}, timerSeg, 2, 2, green,
                                  timerHeigthSize, timerWidthSize);
    // rounds
    //
    double roundHeigthSize = int(HUD_NUM_H / 2.5);
    double roundWidthSize = int(HUD_NUM_W / 2.5);
    lastPosX = renderNumberStream(
            {midScrX - (2 * roundWidthSize), (timerHeigthSize + roundHeigthSize + 8)},
            gameSnapshot.currentRound, 2, 1, green, roundHeigthSize, roundWidthSize);
    lastPosX = renderNumber({lastPosX, (timerHeigthSize + roundHeigthSize + 8)}, 11, green,
                            roundHeigthSize, roundWidthSize);
    lastPosX = renderNumberStream({lastPosX, (timerHeigthSize + roundHeigthSize + 8)},
                                  gameSnapshot.totalRounds, 2, 1, green, roundHeigthSize,
                                  roundWidthSize);

    // ct
    textureManager.getUi(UiType::NumsUI).SetColorMod(0, 0, 255);
    lastPosX = renderNumberStream({midScrX + (4 * timerWidthSize), (timerHeigthSize + 5)},
                                  gameSnapshot.countersWinsRounds, 2, 2, blue, timerHeigthSize,
                                  timerWidthSize);
    // tt,

    textureManager.getUi(UiType::NumsUI).SetColorMod(255, 128, 0);
    lastPosX = renderNumberStream({midScrX - (5 * timerWidthSize) - 2, (timerHeigthSize + 5)},
                                  gameSnapshot.terroristsWinsRounds, 2, 2, orange, timerHeigthSize,
                                  timerWidthSize);
}


void GameRenderer::renderPointer(Coords mouseCoords) {
    Texture& sprite = textureManager.getUi(UiType::CursorUI);
    renderer.Copy(sprite, Rect(0, 0, 50, 50), Rect(mouseCoords.x - 15, mouseCoords.y - 15, 30, 30));
}

int16_t GameRenderer::renderNumberStream(CoordinateInformation pos, int number, int digits,
                                         int separation, RgbValue color, int height, int width) {
    std::vector<int> splittedNumber;

    std::string numStr = std::to_string(number);

    for (char c: numStr) {
        splittedNumber.push_back(c - '0');
    }
    int n = digits - splittedNumber.size();
    if (n > 0) {
        for (int i = 0; i < n; ++i) {
            splittedNumber.insert(splittedNumber.begin(), 0);
        }
    }
    double lastPosX = pos.x - separation;
    for (int number: splittedNumber) {
        lastPosX = renderNumber({lastPosX + separation, pos.y}, number, color, height, width);
    }
    return lastPosX;
}

int16_t GameRenderer::renderNumber(CoordinateInformation posInScreen, int number, RgbValue color,
                                   int height, int width) {

    int numberPos = 48 * number;
    Texture& sprite = textureManager.getUi(UiType::NumsUI);
    sprite.SetColorMod(color.r, color.g, color.b);
    renderer.Copy(sprite, Rect(numberPos, 0, 47, 66),
                  Rect(posInScreen.x, posInScreen.y - height, width, height));

    return (posInScreen.x + width);
}

int16_t GameRenderer::renderSymbol(CoordinateInformation posInScreen, UiSymbol symbol,
                                   RgbValue color) {

    int numberPos = 64 * symbol;
    Texture& sprite = textureManager.getUi(UiType::SymbUI);
    sprite.SetColorMod(color.r, color.g, color.b);
    renderer.Copy(sprite, Rect(numberPos, 0, 64, 64),
                  Rect(posInScreen.x, posInScreen.y - HUD_NUM_H, HUD_NUM_H, HUD_NUM_H));

    return (posInScreen.x + HUD_NUM_H);
}

int16_t GameRenderer::renderWeaponGlyph(CoordinateInformation posInScreen, WeaponType weapon,
                                        RgbValue color) {

    Texture& sprite = textureManager.getWeapon(weapon);
    double multH = static_cast<double>(HUD_NUM_H) / sprite.GetHeight();
    sprite.SetColorMod(color.r, color.g, color.b);
    int offX = 0;
    int offY = -5;
    if (weapon == WeaponType::KNIFE) {
        multH = 1.5;
        offY = 0;
        offX = -20;
    }
    renderer.Copy(sprite, NullOpt,
                  Rect((posInScreen.x - (sprite.GetWidth() * multH) - offX),
                       posInScreen.y - (sprite.GetHeight() * multH / 2) - offY,
                       sprite.GetWidth() * (multH), sprite.GetHeight() * (multH)));

    sprite.SetColorMod(255, 255, 255);
    return (posInScreen.x + (sprite.GetWidth() * multH));
}

void GameRenderer::drawFOVStencil(const CoordinateInformation&, double directionDeg,
                                  double fovDeg, int radius) {

    Uint8 r = 255, g = 255, b = 255, a = 255;

    renderer.SetTarget(textureManager.getFov().SetBlendMode(SDL_BLENDMODE_NONE));

    float xScale = (float(RES_WIDTH) / RES_WIDTH_BASE);
    float yScale = (float(RES_HEIGTH) / RES_HEIGTH_BASE);
    renderer.SetScale(xScale, yScale);

    renderer.SetDrawColor(r / 2, g / 2, b / 2, a);
    renderer.Clear();

    int x0 = RES_WIDTH_BASE / 2;
    int y0 = RES_HEIGTH_BASE / 2;
    int leftSideCone = directionDeg - (fovDeg / 2) - 90;
    int rightSideCone = directionDeg + (fovDeg / 2) - 90;

    filledPieRGBA(renderer.Get(), x0, y0, radius * 3, leftSideCone, rightSideCone, r, g, b, a);
    filledCircleRGBA(renderer.Get(), x0, y0, radius, r, g, b, a);

    renderer.SetTarget();
    SDL_Rect dst = {0, 0, RES_WIDTH_BASE, RES_HEIGTH_BASE};
    renderer.Copy(textureManager.getFov().SetBlendMode(SDL_BLENDMODE_MOD).SetAlphaMod(0),
                  SDL2pp::NullOpt, dst);
}

void GameRenderer::setBuyMenu() {
    RgbValue green(10, 255, 10, 80);
    RgbValue darkGreen(100, 255, 100, 150);
    RgbValue none(255, 255, 255);
    Sint16 rad = 10;
    int borderDist = 50;
    double textPos = (RES_WIDTH_BASE / 2.0) - 50;
    renderText("BUY MENU", {textPos, 20}, 20, green);


    boxRGBA(renderer.Get(), (RES_WIDTH_BASE), 0, 0, (RES_HEIGTH_BASE), 0, 0, 0, 100);

    roundedBoxRGBA(renderer.Get(), (RES_WIDTH_BASE - borderDist), borderDist, (borderDist),
                   (RES_HEIGTH_BASE - borderDist), rad, green.r, green.g, green.b, green.a);

    renderText("AK-47", {RES_WIDTH_BASE / 3.0, (RES_HEIGTH_BASE / 4.0)}, 20, darkGreen);
    renderWeaponGlyph({RES_WIDTH_BASE / 3.0, (RES_HEIGTH_BASE / 4.0)}, WeaponType::AK47, none);
    renderText("BUY MENU", {textPos, 20}, 20, green);
    renderWeaponGlyph({RES_WIDTH_BASE / 3.0, (RES_HEIGTH_BASE / 4.0) * 2}, WeaponType::M3, none);
    renderText("BUY MENU", {textPos, 20}, 20, green);
    renderWeaponGlyph({RES_WIDTH_BASE / 3.0, (RES_HEIGTH_BASE / 4.0) * 3}, WeaponType::AWP, none);
}

void GameRenderer::renderText(std::string text, CoordinateInformation pos, int fontSize,
                              RgbValue color) {
    Texture font = textureManager.getFont(fontSize, text, color);
    renderer.Copy(font, SDL2pp::NullOpt, {(int)pos.x, (int)pos.y});
}

void GameRenderer::render() {
    renderer.Present();
    renderer.SetDrawColor(0, 0, 0, 255);
    renderer.Clear();
}
