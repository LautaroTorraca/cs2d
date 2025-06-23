#include "GameRenderer.h"

#include <cstdint>
// #include <iostream>
#include <string>

#include "Constants/ClientConstants.h"
#include "Constants/PlayerDataConstants.h"
#include "SDL2pp/Optional.hh"
#include "SDL2pp/Texture.hh"
#include "server/Constants/MapTypeConstants.h"
#include "server/GameStatus.h"

#include "CoordinateInformation.h"
#include "EntityConstants.h"
#include "ExplotionSprite.h"
#include "PlayerInformation.h"
#include "PlayerSprite.h"
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
        explotion(renderer, textureManager.getExplotion(), soundManager) {}

bool GameRenderer::setScreen(Snapshot gameSnapshot, MapType map, Coords mouseCoords) {

    if (gameSnapshot.status == GameStatus::GAME_OVER) {
        return false;
    }

    if (playerSprites.size() == 0) {

        for (PlayerInformation player: gameSnapshot.playersInfo) {

            if (player.id == clientID) {
                playerSprites.emplace(player.id, PlayerSprite(renderer, textureManager,
                                                              soundManager, player, true));
            } else {
                playerSprites.emplace(player.id, PlayerSprite(renderer, textureManager,
                                                              soundManager, player, false));
            }
        }
    }
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
        // std::cout << "player: " << currentPlayer.name << "\n";
    }

    offset.x = (gameSnapshot.playersInfo.at(index).position.x) - int(RES_WIDTH_BASE / 2);
    offset.y = (gameSnapshot.playersInfo.at(index).position.y) - int(RES_HEIGTH_BASE / 2);

    renderMap(tileMap, map);
    renderFloorItems(gameSnapshot.dropsInfo);
    renderBomb(gameSnapshot.plantedBombPosition, gameSnapshot.status);
    renderPlayers(gameSnapshot.playersInfo);
    drawFOVStencil(currentPlayer.position, currentPlayer.angle, 60, 50);
    renderUI(gameSnapshot.playersInfo.at(index), gameSnapshot, mouseCoords);
    setRoundWinMenu(gameSnapshot.status);
    stateSounds(gameSnapshot.status);

    if (gameSnapshot.status == GameStatus::GAME_OVER)
        setLeaderBoard(gameSnapshot.playersInfo);

    prevStatus = gameSnapshot.status;
    return true;
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

void GameRenderer::renderBomb(CoordinateInformation pos, GameStatus status) {
    if (pos.x == -1) {
        return;
    }

    if (prevStatus == BOMB_PLANTED && status == BOMB_EXPLODED) {
        explotion.start();
    }

    if (status == BOMB_PLANTED) {

        Texture& sprite = textureManager.getWeapon(EntityType::BOMB);
        CoordinateInformation off(offset.x + 20, offset.y + 7);
        renderer.Copy(sprite, NullOpt,
                      Rect(pos.x - off.x, pos.y - off.y, PLAYER_WIDTH, PLAYER_HEIGTH));
    } else if (status == BOMB_EXPLODED) {

        explotion.draw({pos.x - offset.x, pos.y - offset.y});
    }
}
// HACK: refactor a clase?
void GameRenderer::renderPlayers(std::vector<PlayerInformation> players) {

    for (PlayerInformation player: players) {

        PlayerSprite& playerSprite = playerSprites.at(player.id);

        playerSprite.update(player, offset);
        playerSprite.render();
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
        Texture& wpnSprite = textureManager.getDroppedWeapon((EntityType)item.weapon.weaponType);
        renderFloorWeapon(wpnSprite, item);
    }
}

void GameRenderer::renderFloorWeapon(Texture& sprite, DropInformation wpn) {
    renderer.Copy(sprite, NullOpt,
                  Rect(wpn.position.x - offset.x - 16, wpn.position.y - offset.y - 16,
                       sprite.GetWidth(), sprite.GetHeight()));
}

void GameRenderer::renderUI(PlayerInformation& player, Snapshot gameSnapshot, Coords mouseCoords) {

    RgbValue green(0, 255, 0);
    RgbValue blue(48, 69, 86);
    RgbValue orange(141, 93, 35);

    int midScrX = RES_WIDTH_BASE / 2;
    int midScrY = RES_HEIGTH_BASE / 2;


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
    renderWeaponGlyph({lastPosX, RES_HEIGTH_BASE - HUD_NUM_H},
                      (EntityType)player.actualWeapon.weaponType, green);
    renderNumberStream({(lastPosX + 5), RES_HEIGTH_BASE - 5}, player.actualWeapon.ammoAmount, 3, 2,
                       green);

    //  money
    lastPosX = RES_WIDTH_BASE - (HUD_NUM_W * 7);
    lastPosX = renderSymbol({lastPosX, RES_HEIGTH_BASE - HUD_NUM_H - 10}, UiSymbol::MONEY, green);
    lastPosX = renderNumberStream({(lastPosX), RES_HEIGTH_BASE - HUD_NUM_H - 10},
                                  player.actualMoney, 5, 2, green);

    if (gameSnapshot.status == GameStatus::BOMB_PLANTED) {

        lastPosX = midScrX - (HUD_NUM_W * 3);
        lastPosX = renderSymbol({lastPosX, RES_HEIGTH_BASE - 5}, UiSymbol::TIMER, green);
        lastPosX = renderNumberStream({(lastPosX), RES_HEIGTH_BASE - 5},
                                      (int)gameSnapshot.bombTimer, 2, 2, green);
    }

    // game time
    int timerMin = gameSnapshot.actualTime / 60;
    int timerSeg = int(gameSnapshot.actualTime) % 60;

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

int16_t GameRenderer::renderWeaponGlyph(CoordinateInformation posInScreen, EntityType weapon,
                                        RgbValue color, double mult) {

    Texture& sprite = textureManager.getWeapon(weapon);
    // double multH = static_cast<double>(HUD_NUM_H) / sprite.GetHeight();
    sprite.SetColorMod(color.r, color.g, color.b);
    // int offX = 0;
    // int offY = -5;
    // if (weapon == EntityType::KNIFE || weapon == EntityType::P_AMMO ||
    //     weapon == EntityType::S_AMMO) {
    //     multH = 1.5;
    // offY = 0;
    // offX = -20;
    // }
    renderer.Copy(sprite, NullOpt,
                  Rect((posInScreen.x - (sprite.GetWidth() * mult)),
                       posInScreen.y - (sprite.GetHeight() * mult / 2), sprite.GetWidth() * (mult),
                       sprite.GetHeight() * (mult)));

    sprite.SetColorMod(255, 255, 255);
    return (posInScreen.x + (sprite.GetWidth() * mult));
}

void GameRenderer::drawFOVStencil(const CoordinateInformation&, double directionDeg, double fovDeg,
                                  int radius) {

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
// FIX: colores codigo repetidos.
void GameRenderer::setRoundWinMenu(GameStatus state) {

    if (state != GameStatus::COUNTERS_WIN && state != GameStatus::TERRORISTS_WIN &&
        state != GameStatus::BOMB_EXPLODED) {
        return;
    }
    RgbValue green(10, 255, 10, 80);
    RgbValue lightGreen(150, 255, 150, 200);
    RgbValue none(255, 255, 255);
    Sint16 rad = 10;

    CoordinateInformation pading{50, 150};
    double yOffset = 60;
    double textPosX = 0;
    std::string text;
    if (state == GameStatus::COUNTERS_WIN) {
        text = "Counters Terrorist Wins";
        textPosX = pading.x + 90;
    } else {
        text = "Terrorist Wins";
        textPosX = pading.x + 120;
    }

    roundedBoxRGBA(renderer.Get(), (RES_WIDTH_BASE - pading.x), pading.y - yOffset, (pading.x),
                   (RES_HEIGTH_BASE - pading.y) - yOffset, rad, green.r, green.g, green.b, green.a);

    renderText(text, {textPosX, pading.y + 10 - yOffset}, 20, lightGreen);
}
void GameRenderer::setLeaderBoard(const std::vector<PlayerInformation>& players) {
    RgbValue gray(80, 80, 80, 180);
    RgbValue lightGreen(150, 255, 150, 255);
    RgbValue textColor(220, 220, 220);
    Sint16 rad = 8;

    int boardWidth = RES_WIDTH_BASE * 0.8;
    int boardHeight = RES_HEIGTH_BASE * 0.7;

    double boardX = (RES_WIDTH_BASE - boardWidth) / 2.0;
    double boardY = (RES_HEIGTH_BASE - boardHeight) / 2.0;

    roundedBoxRGBA(renderer.Get(), boardX, boardY, boardX + boardWidth, boardY + boardHeight, rad,
                   gray.r, gray.g, gray.b, gray.a);

    int titleFontSize = 20;
    // Calculate title position to truly center it horizontally
    int titleWidth = textureManager.getFont(titleFontSize, "Leaderboard", lightGreen).GetWidth();
    renderText("Leaderboard", {boardX + (boardWidth - titleWidth) / 2.0, boardY + 10},
               titleFontSize, lightGreen);

    int headerFontSize = 14;
    int colPadding = 10;

    double nameX = boardX + colPadding;
    double killsX = boardX + boardWidth * 0.4;
    double deathsX = boardX + boardWidth * 0.6;
    double moneyX = boardX + boardWidth * 0.8;

    renderText("Name", {nameX, boardY + 40}, headerFontSize, lightGreen);
    renderText("K", {killsX, boardY + 40}, headerFontSize, lightGreen);
    renderText("D", {deathsX, boardY + 40}, headerFontSize, lightGreen);
    renderText("Money", {moneyX, boardY + 40}, headerFontSize, lightGreen);

    double startY = boardY + 65;
    double lineHeight = 18;
    int playerInfoFontSize = 12;
    int numberStreamHeight = 12;
    int numberStreamWidth = 9;


    std::vector<PlayerInformation> sortedPlayers = players;
    std::sort(sortedPlayers.begin(), sortedPlayers.end(),
              [](const PlayerInformation& a, const PlayerInformation& b) {
                  return a.kills > b.kills;
              });

    for (const PlayerInformation& player: sortedPlayers) {

        std::string displayName = player.name;
        if (displayName.length() > 10) {
            displayName = displayName.substr(0, 7) + "...";
        }
        renderText(displayName, {nameX, startY}, playerInfoFontSize, textColor);

        renderNumberStream({killsX - 5, startY + (lineHeight - numberStreamHeight) / 2.0 + 12},
                           player.kills, 2, 2, textColor, numberStreamHeight, numberStreamWidth);
        renderNumberStream({deathsX - 5, startY + (lineHeight - numberStreamHeight) / 2.0 + 12},
                           player.deaths, 2, 2, textColor, numberStreamHeight, numberStreamWidth);
        renderNumberStream({moneyX - 5, startY + (lineHeight - numberStreamHeight) / 2.0 + 12},
                           player.totalMoney, 5, 2, textColor, numberStreamHeight,
                           numberStreamWidth);

        startY += lineHeight;
        if (startY > boardY + boardHeight - lineHeight) {
            break;
        }
    }
}

void GameRenderer::setBuyMenu() {
    RgbValue grey(80, 80, 80, 80);
    RgbValue lightGreen(150, 255, 150, 200);
    RgbValue none(255, 255, 255);
    Sint16 rad = 10;
    int borderDist = 50;
    double textPos = (RES_WIDTH_BASE / 2.0) - 50;
    renderText("BUY MENU", {textPos, 20}, 20, grey);


    boxRGBA(renderer.Get(), (RES_WIDTH_BASE), 0, 0, (RES_HEIGTH_BASE), 0, 0, 0, 100);

    roundedBoxRGBA(renderer.Get(), (RES_WIDTH_BASE - borderDist), borderDist, (borderDist),
                   (RES_HEIGTH_BASE - borderDist), rad, grey.r, grey.g, grey.b, grey.a);

    renderText("AK-47", {90, 60}, 20, lightGreen);
    renderWeaponGlyph({160, 100}, EntityType::AK47, none, 1.5);
    renderBuyButton({170, 100}, 1, 500);

    renderText("   M3", {90, 130}, 20, lightGreen);
    renderWeaponGlyph({160, 170}, EntityType::M3, none, 1.5);
    renderBuyButton({170, 170}, 2, 1500);

    renderText("  AWP", {90, 200}, 20, lightGreen);
    renderWeaponGlyph({160, 240}, EntityType::AWP, none, 1.5);
    renderBuyButton({170, 240}, 3, 2500);

    renderText("PRIMARY", {260, 73}, 12, lightGreen);
    renderText("    AMMO", {260, 85}, 12, lightGreen);
    renderWeaponGlyph({320, 120}, EntityType::P_AMMO, none, 3);
    renderBuyButton({330, 100}, 9, 100);

    renderText("SECONDARY", {260, 153}, 12, lightGreen);
    renderText("    AMMO", {260, 165}, 12, lightGreen);
    renderWeaponGlyph({330, 215}, EntityType::S_AMMO, none, 4.5);
    renderBuyButton({330, 200}, 0, 50);
}
void GameRenderer::renderBuyButton(CoordinateInformation pos, int button, int price) {

    RgbValue green(10, 255, 10, 150);
    RgbValue gray(64, 64, 64, 200);
    RgbValue lightGreen(150, 255, 150, 200);
    RgbValue none(255, 255, 255);

    int width = 55;
    int height = 50;
    int rad = 8;

    double x1 = pos.x + width;
    double y1 = pos.y - (height / 2.0);
    double x2 = pos.x;
    double y2 = pos.y + (height / 2.0);

    roundedBoxRGBA(renderer.Get(), x2, y1, x1, y2, rad, gray.r, gray.g, gray.b, gray.a);

    std::string line1 = "Buy [" + std::to_string(button) + "]";
    std::string line2 = "  " + std::to_string(price);

    int textOffsetX = 5;
    int textHeight = 14;

    renderText(line1.c_str(), {x2 + textOffsetX, y1 + 2}, textHeight, green);
    renderText(line2.c_str(), {x2 + textOffsetX + 5, y1 + 2 + textHeight + 5}, textHeight, green);
}


void GameRenderer::renderText(std::string text, CoordinateInformation pos, int fontSize,
                              RgbValue color) {
    Texture font = textureManager.getFont(fontSize, text, color);
    renderer.Copy(font, SDL2pp::NullOpt, {(int)pos.x, (int)pos.y});
}

void GameRenderer::stateSounds(GameStatus state) {
    if (prevStatus == GameStatus::ON_GOING && state == GameStatus::BOMB_PLANTED) {
        soundManager.playBombPlanted();
    } else if (prevStatus == GameStatus::ON_GOING && state == GameStatus::COUNTERS_WIN) {
        soundManager.playCtWins();
    } else if (prevStatus == GameStatus::BOMB_PLANTED && state == GameStatus::COUNTERS_WIN) {
        soundManager.playCtWinsBombDefused();
    } else if ((prevStatus == GameStatus::ON_GOING || prevStatus == GameStatus::BOMB_PLANTED) &&
               state == GameStatus::TERRORISTS_WIN) {
        soundManager.playTtWins();
    }
}

void GameRenderer::render() {
    renderer.Present();
    renderer.SetDrawColor(0, 0, 0, 255);
    renderer.Clear();
}
