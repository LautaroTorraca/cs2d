// TODO: ver QT para el menu.
#include <exception>
#include <iostream>

#include "GameClient.h"
// #include "SDL_events.h"
// #include "gameConstants.h"
// #include "_deps/sdl2_image-src/include/SDL_image.h"
// #include "common/Constants/PlayerDataConstants.h"
// #include "gameConstants.h"
#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>
using namespace DTO;
// #include "weaponConstants.h"

// TODO: cono de luz

int main() {
  try {
    GameClient game;
    game.run();
    return 0;

  } catch (std::exception &e) {

    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }
}
