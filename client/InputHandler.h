#pragma once

#include "Constants/PlayerDataConstants.h"
#include "server/DTO/GameLobbyDTO.h"

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
