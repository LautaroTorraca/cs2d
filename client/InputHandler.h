#pragma once

// #include <SDL2pp/SDL2pp.hh> //HACK: devolver por vscode

#include "Constants/PlayerDataConstants.h"
#include "server/DTO/GameLobbyDTO.h"
// #include "server/DTO/LobbyConnectionDTO.h"
#include "Protocol.h"
#include "SDL_events.h"

using namespace DTO;

class InputHandler {
private:
    Protocol& protocol;
    Coords mouseCoords;

public:
    InputHandler(Protocol& protocol);
    void processCommand();
    bool processEvent(SDL_Event event);
    Coords getMouseCoords();
    GameLobbyDTO clientInput();
};
