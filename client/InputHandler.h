#pragma once
// #include "SDL2pp/Texture.hh"
// #include "TextureManager.h"
// #include "playerDataConstants.h"
// #include "weaponConstants.h"

#include "Protocol.h"
//#include "SDL_events.h" //COMENTADO PARA MAKE
#include <SDL2pp/SDL2pp.hh>

#include "cmake-build-debug/_deps/sdl2_mixer-src/Xcode/macOS/SDL2.framework/Versions/Current/Headers/SDL_events.h"
//
// using namespace SDL2pp;
// using namespace DTO;

class InputHandler {
private:
  Protocol &protocol;

public:
  InputHandler(Protocol &protocol);
  void processCommand();
  bool processEvent(SDL_Event event);
};
