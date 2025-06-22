#include "GameClient.h"

#include <iostream>
#include <sstream>

#include <bits/types/error_t.h>
#include <qapplication.h>
#include <qdialog.h>

#include "client/GameRenderer.h"
// #include "server/Constants/ConnectionStatus.h"
#include "server/Constants/MapTypeConstants.h"
// #include "server/DTO/GameLobbyDTO.h"
// #include "server/DTO/LobbyConnectionDTO.h"
// #include "server/DTO/LobbyConnectionDTO.h"
// #include "server/DTO/PlayerChoicesDTO.h"
// #include "server/Team.h"

#include "InputHandler.h"
#include "Protocol.h"
#include "SDL_timer.h"

using std::stringstream;

using namespace SDL2pp;
using namespace DTO;

GameClient::GameClient(Protocol& protocol):
        running(true), protocol(protocol), inputHandler(protocol) {}

void GameClient::run() {

    PreSnapshot preSnapshot = protocol.receivePreSnapshot();
    GameRenderer renderer(preSnapshot.map, preSnapshot.clientId);

    bool running = true;
    const int FPS = 1000;
    const int frameDelay = 1000 / FPS;
    uint32_t frameStart = SDL_GetTicks();
    int frameTime;
    SDL sdl(SDL_INIT_VIDEO);
    try {
        while (running) {
            // gameSnapshot = protocol.receiveSnapshot();
            SDL_Event event;
            if (SDL_PollEvent(&event)) {
                running = inputHandler.processEvent(event);
            }
            frameTime = SDL_GetTicks() - frameStart;

            if (frameDelay <= frameTime) {
                // FIX: cambiar harcodeada de mapa.
                renderer.renderScreen(protocol.receiveSnapshot(), MapType::DUST,
                                      inputHandler.getMouseCoords());
                frameStart = SDL_GetTicks();
            }
        }
    } catch (...) {}
}
