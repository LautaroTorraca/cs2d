#include "GameClient.h"
#include "InputHandler.h"
#include "Protocol.h"
#include "client/GameRenderer.h"

using namespace SDL2pp;
using namespace DTO;

GameClient::GameClient()
    : running(true), protocol(PORT, HOSTNAME), inputHandler(protocol) {}

void GameClient::run() {
  PreSnapshot preSnapshot = protocol.receivePreSnapshot();
  GameRenderer renderer(preSnapshot.map, preSnapshot.clientId);

  bool running = true;
  const int FPS = 60;
  const int frameDelay = 1000 / FPS;
  int32_t frameStart = SDL_GetTicks();
  int frameTime;
  SDL sdl(SDL_INIT_VIDEO);

  while (running) {
    // gameSnapshot = protocol.receiveSnapshot();
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      running = inputHandler.processEvent(event);
      frameTime = SDL_GetTicks() - frameStart;

      if (frameDelay <= frameTime) {
        renderer.renderScreen(protocol.receiveSnapshot());
        frameStart = SDL_GetTicks();
      }
    }
  }
}
