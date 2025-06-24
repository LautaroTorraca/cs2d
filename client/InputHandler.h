#pragma once

#include "Constants/PlayerDataConstants.h"
#include "server/GameStatus.h"

#include "Protocol.h"
#include "SDL_events.h"

using namespace DTO;
using namespace Client;
class InputHandler {
private:
    Protocol& protocol;
    Coords mouseCoords;
    bool inBuyMenu = false;

public:
    // InputHandler(Protocol& protocol);
    InputHandler(Protocol& protocol);
    bool processEvents(SDL_Event& event, GameStatus status, double res_h, double res_w);
    void checkDiagonalMovement();
    // bool processEvents(SDL_Event & event, GameStatus status);
    bool isInMenu();
    Coords getMouseCoords();
};
