// TODO: ver QT para el menu.
#include <cstdint>
#include <exception>
#include <iostream>
#include <vector>

#include "SDL_events.h"
#include "SDL_timer.h"
// #include "gameConstants.h"
// #include "_deps/sdl2_image-src/include/SDL_image.h"
#include "gameConstants.h"
#include "playerDataConstants.h"
#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "GameRenderer.h"
#include "weaponConstants.h"

using namespace SDL2pp;
using namespace DTO;

// #define PLYW 50
// #define PLYH 50
// constexpr int PLAYER_HEIGTH = 50;
// constexpr int PLAYER_WIDTH = 50;
//
// constexpr int RES_WIDTH = 640;
// constexpr int RES_HEIGTH = 400;

// TODO: cono de luz

snapshot fillDummies() {

  std::vector<PlayerData> playerList;
  std::vector<std::vector<int>> tileMap(MAP_HEIGHT,
                                        std::vector<int>(MAP_WIDTH, 30));

  tileMap[4][0] = 60;
  tileMap[4][1] = 61;
  tileMap[4][2] = 62;
  // tileMap[14][10] = 60;
  // tileMap[14][11] = 61;
  // tileMap[14][12] = 62;
  // std::vector<std::vector<int>> tileMap;

  PlayerData player1;
  PlayerData player2;
  PlayerData player3;

  player1.nombre = "Juan";
  player1.id = 1234;
  player1.coords.x = 50; // RES_WIDTH / 2;
  player1.coords.y = 50; // RES_HEIGTH / 2;
  player1.stats = {100, 50};
  player1.angle = 0;
  player1.skin = GameConstants::Skins::ARCTIC_AVENGER;
  player1.team = GameConstants::Team::COUNTER_TERRORISTS;

  player2.nombre = "Ana";
  player2.id = 5678;
  player2.coords.x = 155;
  player2.coords.y = player1.coords.y - 5;
  player2.stats = {80, 60};
  player2.angle = 120;
  player2.skin = GameConstants::Skins::GUERRILLA;
  player2.team = GameConstants::Team::TERRORISTS;

  player3.nombre = "Ana222";
  player3.id = 568;
  player3.coords.x = player1.coords.x - 25;
  player3.coords.y = player1.coords.y - 25;
  player3.stats = {80, 60};
  player3.angle = 270;
  player3.skin = GameConstants::Skins::L337_KREW;
  player3.team = GameConstants::Team::TERRORISTS;

  playerList.push_back(player1);
  playerList.push_back(player2);
  playerList.push_back(player3);
  //
  snapshot gameSnapshot;
  gameSnapshot.game.players = playerList;
  gameSnapshot.game.map.tileMap = tileMap;
  gameSnapshot.clientId = 1234;
  // aca seteo que tan a la izquierda se va
  // el mapa cuando arranca a renderizar
  // gameSnapshot.offset.y = 0; // TILE_HEIGHT * 4;
  // gameSnapshot.offset.x = 0; // TILE_WIDTH * 4;

  std::vector<DroppedWeaponDTO> weaponList;

  DroppedWeaponDTO ak_1;
  ak_1.id = WeaponConstants::AK47;
  ak_1.pos.x = 30;
  ak_1.pos.y = 25;
  ak_1.angle = 0;
  DroppedWeaponDTO ak_2;
  ak_2.id = WeaponConstants::AK47;
  ak_2.pos.x = 15;
  ak_2.pos.y = 40;
  ak_2.angle = 220;
  DroppedWeaponDTO m3_1;
  m3_1.id = WeaponConstants::M3;
  m3_1.pos.x = 80;
  m3_1.pos.y = 110;
  m3_1.angle = 330;
  DroppedWeaponDTO glock_1;
  glock_1.id = WeaponConstants::GLOCK;
  glock_1.pos.x = 300;
  glock_1.pos.y = 10;
  glock_1.angle = 60;
  DroppedWeaponDTO bomb;
  bomb.id = WeaponConstants::BOMB;
  bomb.pos.x = 190;
  bomb.pos.y = 130;
  bomb.angle = 60;
  DroppedWeaponDTO awp;
  awp.id = WeaponConstants::AWP;
  awp.pos.x = 130;
  awp.pos.y = 190;
  awp.angle = 60;

  weaponList.push_back(ak_1);
  weaponList.push_back(m3_1);
  weaponList.push_back(glock_1);
  weaponList.push_back(ak_2);
  weaponList.push_back(bomb);
  weaponList.push_back(awp);

  gameSnapshot.game.map.droppedWeapons = weaponList;

  return gameSnapshot;
}

int main() try {

  SDL sdl(SDL_INIT_VIDEO);
  GameRenderer renderer;
  snapshot gameSnapshot = fillDummies();

  // Cubo properties   ()//x, y, width, height
  // for (PlayerData player : playerList) {
  //   Rect playerCube(player.coords.x, player.coords.y, PLAYER_WIDTH,
  //                   PLAYER_HEIGTH);
  //   cubeList.push_back(playerCube);
  // }

  int moveSpeedY = TILE_HEIGHT / 4;
  int moveSpeedX = TILE_WIDTH / 4;

  bool running = true;
  const int FPS = 60;
  const int frameDelay = 1000 / FPS;
  int32_t frameStart = SDL_GetTicks();
  int frameTime;

  while (running) {

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
      } else if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_UP:
          // protocol.move(Direction::up);

          gameSnapshot.game.players.front().coords.y -= moveSpeedY;
          break;
        case SDLK_DOWN:
          // cubeRect.y += moveSpeed;
          // protocol.move(Direction::down);
          // gameSnapshot.players.front().coords.y += moveSpeedY;
          gameSnapshot.game.players.front().coords.y += moveSpeedY;
          break;
        case SDLK_LEFT:
          // cubeRect.x -= moveSpeed;
          // protocol.move(Direction::left);
          // gameSnapshot.players.front().coords.x -= moveSpeedX;
          gameSnapshot.game.players.front().coords.x -= moveSpeedX;
          break;
        case SDLK_RIGHT:
          // cubeRect.x += moveSpeed;
          // protocol.move(Direction::right);
          gameSnapshot.game.players.front().coords.x += moveSpeedX;
          break;
        case SDLK_w:
          gameSnapshot.game.players.back().coords.y -= moveSpeedY;
          break;
        case SDLK_a:
          gameSnapshot.game.players.back().coords.x -= moveSpeedX;
          break;
        case SDLK_s:
          gameSnapshot.game.players.back().coords.y += moveSpeedY;
          break;
        case SDLK_d:
          gameSnapshot.game.players.back().coords.x += moveSpeedX;
          break;
        case SDLK_ESCAPE:
          running = false;
          break;
          // case SDL_MOUSEMOTION:
          //   event.caxis;
          //   break;
        }
      } else if (event.type == SDL_MOUSEMOTION) {

        // int centerX = RES_WIDTH / 2;
        // int centerY = RES_HEIGTH / 2;
        //
        // int mouseX = event.motion.x;
        // int mouseY = event.motion.y;

        int dx = event.motion.x - (RES_WIDTH / 2);
        int dy = event.motion.y - (RES_HEIGTH / 2);

        double angleInRads = atan2(dy, dx);

        double angleInDegree = angleInRads * 180.0 / M_PI;

        angleInDegree += 90;

        gameSnapshot.game.players.front().angle = angleInDegree;
        std::cout << "angulo: " << angleInDegree << "\n";
      }

      frameTime = SDL_GetTicks() - frameStart;
      if (frameDelay <= frameTime) {
        renderer.renderScreen(gameSnapshot);
        frameStart = SDL_GetTicks();
      }
    }
  }

  return 0;
} catch (std::exception &e) {
  std::cerr << "Error: " << e.what() << std::endl;
  return 1;
}
