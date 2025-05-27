#include "GameRenderer.h"
// #include "SDL_blendmode.h"
// #include "SDL_timer.h"
#include "SDL2pp/Optional.hh"
#include "client/playerDataConstants.h"
#include "gameConstants.h"
// #include "weaponConstants.h"
#include <SDL2pp/SDL2pp.hh>

#include <SDL2pp/Point.hh>
#include <SDL2pp/Rect.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/SDL.hh>
#include <SDL2pp/Surface.hh>
#include <SDL2pp/Texture.hh>
#include <SDL2pp/Window.hh>
// #include <cstddef>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <linux/kd.h>
// #include <memory>
#include <string>
#include <vector>
// #include <vector>

GameRenderer::GameRenderer()
    : window("CS-Go 2D???", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
             RES_WIDTH, RES_HEIGTH, 0),
      renderer(window, -1, SDL_RENDERER_ACCELERATED), textureManager(renderer) {
}

void GameRenderer::renderScreen(snapshot gameSnapshot) {
  renderer.Clear();

  // std::unique_ptr<PlayerData> currentPlayer;
  Coords offsetCoords;
  for (PlayerData player : gameSnapshot.game.players) {
    if (player.id == gameSnapshot.clientId) {
      offsetCoords = player.coords;
      break;
    }
  }

  // size_t targetId = gameSnapshot.clientId;
  // auto it = std::find_if(
  //     gameSnapshot.playerList.begin(), gameSnapshot.playerList.end(),
  //     [targetId](const PlayerData &p) { return p.id == targetId; });
  // if (it == gameSnapshot.playerList.end())
  //   throw -1;
  offsetCoords.x -= RES_WIDTH / 2;
  offsetCoords.y -= RES_HEIGTH / 2;

  renderMap(gameSnapshot.game.map.tileMap, offsetCoords);
  renderFloorItems(gameSnapshot.game.map.droppedWeapons, offsetCoords);
  renderPlayers(gameSnapshot.game.players, offsetCoords, gameSnapshot.clientId);
  // renderPlayersAsCubes(gameSnapshot.players);

  renderer.Present();
}

void GameRenderer::renderMap(std::vector<std::vector<int>> tileMap,
                             Coords offset) {

  // TODO: que cambie el mapa con el snapshot

  Texture &tileMapTexture = textureManager.getTileMap(GameConstants::DUST);

  int posCounter = 0;
  for (std::vector<int> tileRow : tileMap) {
    for (int tile : tileRow) {

      renderTile(tileMapTexture, tile, posCounter, offset);
      posCounter++;
    }
  }
}

void GameRenderer::renderPlayers(std::vector<PlayerData> players, Coords offset,
                                 size_t clientId) {

  // Texture &sprite =
  //     textureManager.getSkin(GameConstants::Skins::ARCTIC_AVENGER);

  // PlayerData current_player = players.front();
  // players.erase(players.begin());

  srand(time(nullptr));
  int numero = rand() % 6;
  // renderCurrentPlayer(sprite, current_player, numero, offset);

  for (PlayerData player : players) {
    Texture &skin = textureManager.getSkin(player.skin);
    if (player.id == clientId)
      renderCurrentPlayer(skin, player, numero, offset);
    else
      renderPlayer(skin, player, numero, offset);
  }
}

void GameRenderer::renderPlayersAsCubes(std::vector<PlayerData> players) {
  for (PlayerData player : players) {

    Rect playerCube(player.coords.x, player.coords.y, PLAYER_WIDTH,
                    PLAYER_HEIGTH);

    if (player.team == GameConstants::Team::TERRORISTS) {
      renderer.SetDrawColor(196, 162, 64, 255);
    } else {
      renderer.SetDrawColor(43, 38, 122, 255);
    }
    renderer.FillRect(playerCube);
  }
}

void GameRenderer::renderPlayer(Texture &sprite, PlayerData player,
                                int variation, Coords offset) {

  int posX = TILE_SRC_SIZE * (variation % 2);
  int div = (variation / 2);
  int posY = TILE_SRC_SIZE * div;

  renderer.Copy(sprite, Rect(posX, posY, TILE_SRC_SIZE, TILE_SRC_SIZE),
                Rect(player.coords.x - offset.x, player.coords.y - offset.y,
                     PLAYER_WIDTH, PLAYER_HEIGTH),
                player.angle);
}

void GameRenderer::renderCurrentPlayer(Texture &sprite, PlayerData player,
                                       int variation, Coords offset) {

  int posX = TILE_SRC_SIZE * (variation % 2);
  int div = (variation / 2);
  int posY = TILE_SRC_SIZE * div;

  offset.x = offset.x;

  renderer.Copy(
      sprite, Rect(posX, posY, TILE_SRC_SIZE, TILE_SRC_SIZE),
      Rect(RES_WIDTH / 2, RES_HEIGTH / 2, PLAYER_WIDTH, PLAYER_HEIGTH),
      player.angle);
  // renderer.Copy(sprite, Rect(posX, posY, TILE_SRC_SIZE, TILE_SRC_SIZE),
  //               Rect(player.coords.x - (offset.x), player.coords.y -
  //               (offset.y),
  //                    PLAYER_WIDTH, PLAYER_HEIGTH),
  //               player.angle);
}

void GameRenderer::renderTile(Texture &mapTile, int tile, int pos,
                              Coords offset) {

  int textureX = TILE_SRC_SIZE * (tile % 5);
  int div = (tile / 5);
  int textureY = TILE_SRC_SIZE * div;

  int posX = TILE_WIDTH * (pos % MAP_WIDTH);
  int div2 = (pos / MAP_WIDTH);
  int posY = TILE_HEIGHT * div2;

  renderer.Copy(
      mapTile, Rect(textureX, textureY, TILE_SRC_SIZE, TILE_SRC_SIZE),
      Rect(posX - offset.x, posY - offset.y, TILE_WIDTH, TILE_HEIGHT));
}

void GameRenderer::renderFloorItems(std::vector<DroppedWeaponDTO> weaponList,
                                    Coords offset) {

  for (DroppedWeaponDTO weapon : weaponList) {
    Texture &wpnSprite = textureManager.getDroppedWeapon(weapon.id);
    renderFloorWeapon(wpnSprite, weapon, offset);
  }
}

void GameRenderer::renderFloorWeapon(Texture &sprite, DroppedWeaponDTO wpn,
                                     Coords offset) {
  renderer.Copy(sprite, NullOpt,
                Rect(wpn.pos.x - offset.x, wpn.pos.y - offset.y,
                     sprite.GetWidth() * WPN_SZ_MULT,
                     sprite.GetHeight() * WPN_SZ_MULT),
                wpn.angle);
}

//
