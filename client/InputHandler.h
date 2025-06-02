#pragma once
// #include "SDL2pp/Texture.hh"
// #include "TextureManager.h"
// #include "playerDataConstants.h"
// #include "weaponConstants.h"

#include "Protocol_testing.h"
#include "SDL_events.h"
#include <SDL2pp/SDL2pp.hh>
//
// using namespace SDL2pp;
// using namespace DTO;

class InputHandler {
private:
  ProtocolTesting &protocol;

public:
  InputHandler(ProtocolTesting &protocol);
  void processCommand();
  bool processEvent(SDL_Event event);
};
