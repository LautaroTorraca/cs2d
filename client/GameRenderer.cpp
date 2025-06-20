#include "GameRenderer.h"

#include <cstdint>
#include <iostream>
#include <string>

#include "Constants/ClientConstants.h"
#include "Constants/PlayerDataConstants.h"
#include "SDL2pp/Optional.hh"
#include "SDL2pp/Texture.hh"
#include "server/Constants/MapTypeConstants.h"
// #include "server/GameStatus.h"
#include "server/Game.h"
#include "server/WeaponConstants.h"

#include "CoordinateInformation.h"
#include "PlayerInformation.h"
#include "ProjectileInformation.h"
#include "SDL2_gfxPrimitives.h"
#include "SDL_blendmode.h"
#include "SDL_stdinc.h"
#include "SnapshotConstants.h"
#include "TextureManager.h"


GameRenderer::GameRenderer(std::vector<std::vector<uint8_t>> tileMap, size_t clientId):
        window("CS-Go 2D???", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, RES_WIDTH,
               RES_HEIGTH, 0),
        renderer(window, -1, SDL_RENDERER_ACCELERATED),
        textureManager(renderer),
        tileMap(tileMap),
        clientID(clientId) {}

void GameRenderer::renderScreen(Snapshot gameSnapshot, MapType map, Coords mouseCoords) {

    renderer.SetDrawColor(0, 0, 0, 255);
    renderer.Clear();

    float xScale = (float(RES_WIDTH) / RES_WIDTH_BASE);
    float yScale = (float(RES_HEIGTH) / RES_HEIGTH_BASE);

    // float xScale = 2;
    // float yScale = 2;
    std::cout << "x: " << xScale << " y: " << yScale << " \n";
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
    renderer.Present();
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

    renderer.Copy(sprite, NullOpt,
                  Rect(pos.x - offset.x, pos.y - offset.y, PLAYER_WIDTH, PLAYER_HEIGTH));
}

void GameRenderer::renderPlayers(std::vector<PlayerInformation> players, size_t clientId) {

    srand(time(nullptr));
    int numero = rand() % 6;

    for (PlayerInformation player: players) {
        Texture& skin = textureManager.getSkin(player.skin);
        if (player.id == clientId)
            renderCurrentPlayer(skin, player, numero);
        else
            renderPlayer(skin, player, numero);
        renderBullets(player);
    }
}

void GameRenderer::renderPlayer(Texture& sprite, PlayerInformation player, int variation) {

    int posSrcX = TILE_SRC_SIZE * (variation % 2);
    int div = (variation / 2);
    int posSrcY = TILE_SRC_SIZE * div;

    // int(RES_WIDTH_BASE / 2);
    int relPosX = player.position.x - offset.x - int(RES_WIDTH_BASE / 2);
    int relPosY = player.position.y - offset.y - int(RES_HEIGTH_BASE / 2);
    std::cout << "diferencia en X de currentPlayer y el otro: " << std::to_string(relPosX) << "\n";
    std::cout << "diferencia en Y de currentPlayer y el otro: " << std::to_string(relPosY)
              << "\n\n";

    int offsetX = PLAYER_WIDTH / 2;
    int offsetY = PLAYER_HEIGTH / 2;
    int posPlayerX = ((RES_WIDTH_BASE) / 2) + relPosX - offsetX;
    int posPlayerY = ((RES_HEIGTH_BASE) / 2) + relPosY - offsetY;

    renderer.Copy(sprite, Rect(posSrcX, posSrcY, TILE_SRC_SIZE, TILE_SRC_SIZE),
                  Rect(posPlayerX, posPlayerY, PLAYER_WIDTH, PLAYER_HEIGTH), player.angle);
}

void GameRenderer::renderCurrentPlayer(Texture& sprite, PlayerInformation player, int variation) {

    int posX = TILE_SRC_SIZE * (variation % 2);
    int div = (variation / 2);
    int posY = TILE_SRC_SIZE * div;

    int offsetX = PLAYER_WIDTH / 2;
    int offsetY = PLAYER_HEIGTH / 2;
    // offset.x = offset.x;

    renderer.Copy(sprite, Rect(posX, posY, TILE_SRC_SIZE, TILE_SRC_SIZE),
                  Rect(RES_WIDTH_BASE / 2 - offsetX, RES_HEIGTH_BASE / 2 - offsetY, PLAYER_WIDTH,
                       PLAYER_HEIGTH),
                  player.angle);
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

    for (DropInformation weapon: weaponList) {
        Texture& wpnSprite = textureManager.getDroppedWeapon(weapon.weapon.weaponType);
        renderFloorWeapon(wpnSprite, weapon);
    }
}

void GameRenderer::renderFloorWeapon(Texture& sprite, DropInformation wpn) {
    renderer.Copy(sprite, NullOpt,
                  Rect(wpn.position.x - offset.x, wpn.position.y - offset.y,
                       sprite.GetWidth() * WPN_SZ_MULT, sprite.GetHeight() * WPN_SZ_MULT));
}

void GameRenderer::renderUI(PlayerInformation& player, Snapshot gameSnapshot, Coords mouseCoords) {

    renderPointer(mouseCoords);
    // if (gameSnapshot.status == BUY_TIME) {
    renderSymbol({RES_WIDTH_BASE - HUD_NUM_H, RES_HEIGTH_BASE - HUD_NUM_H * 4 - 10}, UiSymbol::BUY);
    // }

    // health
    int healthNum1 = player.actualHealthPoints / 100;        // Primer dígito
    int healthNum2 = (player.actualHealthPoints / 10) % 10;  // Segundo dígito
    int healthNum3 = player.actualHealthPoints % 10;         // Tercer dígito
    int16_t lastPosX = 0;
    lastPosX = renderSymbol({5, RES_HEIGTH_BASE - 5}, UiSymbol::HEALTH);
    lastPosX = renderNumber({static_cast<int16_t>(lastPosX + 5), RES_HEIGTH_BASE - 5}, healthNum1);
    lastPosX = renderNumber({static_cast<int16_t>(lastPosX + 5), RES_HEIGTH_BASE - 5}, healthNum2);
    lastPosX = renderNumber({static_cast<int16_t>(lastPosX + 5), RES_HEIGTH_BASE - 5}, healthNum3);

    // bullets
    int bulletsNum1 = player.actualWeapon.ammoAmount / 100;        // Primer dígito
    int bulletsNum2 = (player.actualWeapon.ammoAmount / 10) % 10;  // Segundo dígito
    int bulletsNum3 = player.actualWeapon.ammoAmount % 10;         // Tercer dígito

    lastPosX = RES_WIDTH_BASE - (HUD_NUM_W * 3) - 20;

    renderWeaponGlyph({lastPosX, RES_HEIGTH_BASE - HUD_NUM_H}, player.actualWeapon.weaponType);
    lastPosX = renderNumber({static_cast<int16_t>(lastPosX + 5), RES_HEIGTH_BASE - 5}, bulletsNum1);
    lastPosX = renderNumber({static_cast<int16_t>(lastPosX + 5), RES_HEIGTH_BASE - 5}, bulletsNum2);
    lastPosX = renderNumber({static_cast<int16_t>(lastPosX + 5), RES_HEIGTH_BASE - 5}, bulletsNum3);

    //  money
    int moneyNum1 = player.actualMoney / 10000;        // Primer dígito
    int moneyNum2 = (player.actualMoney / 1000) % 10;  // Segundo dígito
    int moneyNum3 = (player.actualMoney / 100) % 10;   // Tercer dígito
    int moneyNum4 = (player.actualMoney / 10) % 10;    // Cuarto dígito
    int moneyNum5 = player.actualMoney % 10;           // Quinto dígito

    lastPosX = RES_WIDTH_BASE - (HUD_NUM_W * 6) - 35;

    lastPosX = renderSymbol({lastPosX, RES_HEIGTH_BASE - HUD_NUM_H - 10}, UiSymbol::MONEY);
    lastPosX = renderNumber({static_cast<int16_t>(lastPosX + 5), RES_HEIGTH_BASE - HUD_NUM_H - 10},
                            moneyNum1);
    lastPosX = renderNumber({static_cast<int16_t>(lastPosX + 5), RES_HEIGTH_BASE - HUD_NUM_H - 10},
                            moneyNum2);
    lastPosX = renderNumber({static_cast<int16_t>(lastPosX + 5), RES_HEIGTH_BASE - HUD_NUM_H - 10},
                            moneyNum3);
    lastPosX = renderNumber({static_cast<int16_t>(lastPosX + 5), RES_HEIGTH_BASE - HUD_NUM_H - 10},
                            moneyNum4);
    lastPosX = renderNumber({static_cast<int16_t>(lastPosX + 5), RES_HEIGTH_BASE - HUD_NUM_H - 10},
                            moneyNum5);

    // time left to defuse
    lastPosX = renderSymbol(
            {(RES_WIDTH_BASE / 2) - (HUD_NUM_H) - (HUD_NUM_H / 2), RES_HEIGTH_BASE - 5},
            UiSymbol::TIMER);
    int timerNum1 = gameSnapshot.actualTime / 100;           // Primer dígito
    int timerNum2 = int(gameSnapshot.actualTime / 10) % 10;  // Segundo dígito
    std::cout << "<<<< timer: " << gameSnapshot.actualTime << ">>>>\n";
    lastPosX = renderNumber({static_cast<int16_t>(lastPosX + 5), RES_HEIGTH_BASE - 5}, timerNum1);
    lastPosX = renderNumber({static_cast<int16_t>(lastPosX + 5), RES_HEIGTH_BASE - 5}, timerNum2);
}

void GameRenderer::renderPointer(Coords mouseCoords) {
    Texture& sprite = textureManager.getUi(UiType::CursorUI);
    renderer.Copy(sprite, Rect(0, 0, 50, 50), Rect(mouseCoords.x - 15, mouseCoords.y - 15, 30, 30));
}

int16_t GameRenderer::renderNumber(Coords posInScreen, int number) {

    int numberPos = 48 * number;
    Texture& sprite = textureManager.getUi(UiType::NumsUI);
    sprite.SetColorMod(0, 255, 0);
    renderer.Copy(sprite, Rect(numberPos, 0, 47, 66),
                  Rect(posInScreen.x, posInScreen.y - HUD_NUM_H, HUD_NUM_W, HUD_NUM_H));

    return (posInScreen.x + HUD_NUM_W);
}

int16_t GameRenderer::renderSymbol(Coords posInScreen, UiSymbol symbol) {

    int numberPos = 64 * symbol;
    Texture& sprite = textureManager.getUi(UiType::SymbUI);
    sprite.SetColorMod(0, 255, 0);
    renderer.Copy(sprite, Rect(numberPos, 0, 64, 64),
                  Rect(posInScreen.x, posInScreen.y - HUD_NUM_H, HUD_NUM_H, HUD_NUM_H));

    return (posInScreen.x + HUD_NUM_H);
}

int16_t GameRenderer::renderWeaponGlyph(Coords posInScreen, WeaponType weapon) {

    Texture& sprite = textureManager.getWeapon(weapon);
    double multH = static_cast<double>(HUD_NUM_H) / sprite.GetHeight();
    sprite.SetColorMod(0, 255, 0);
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

    return (posInScreen.x + (sprite.GetWidth() * multH));
}

void GameRenderer::drawFOVStencil(const CoordinateInformation& playerCoords, double directionDeg,
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
