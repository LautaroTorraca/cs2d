#include "InputHandler.h"

#include "Constants/PlayerDataConstants.h"
// #include "build/_deps/sdl2-src/src/joystick/hidapi/steam/controller_constants.h"
// #include "server/DTO/GameLobbyDTO.h"
// #include "server/DTO/LobbyConnectionDTO.h"

#include "Constants/ClientConstants.h"

#include "MoveConstants.h"
#include "SDL_events.h"
#include "SDL_mouse.h"

InputHandler::InputHandler(Protocol& protocol): protocol(protocol) {}

bool InputHandler::processEvent(SDL_Event event) {
    if (event.type == SDL_QUIT) {
        protocol.exit();
    } else if (event.type == SDL_KEYDOWN) {

        switch (event.key.keysym.sym) {
            case SDLK_UP:
                protocol.move(Up);
                break;
            case SDLK_DOWN:
                protocol.move(Down);
                break;
            case SDLK_LEFT:
                protocol.move(Left);
                break;
            case SDLK_RIGHT:
                protocol.move(Right);
                break;
            case SDLK_1:
                protocol.changeWeapon(0);
                break;
            case SDLK_2:
                protocol.changeWeapon(1);
                break;
            case SDLK_3:
                protocol.changeWeapon(2);
                break;
            case SDLK_4:
                protocol.changeWeapon(3);
                break;
            case SDLK_f:
                protocol.defuseBomb();
                break;
            case SDLK_j:
                protocol.buy({ProductTypes::AK_47_WEAPON, 1});
                break;
            case SDLK_k:
                protocol.buy({ProductTypes::M3_WEAPON, 1});
                break;
            case SDLK_l:
                protocol.buy({ProductTypes::AWP_WEAPON, 1});
                break;
            case SDLK_ESCAPE:
                protocol.exit();
        }
    } else if (event.type == SDL_MOUSEBUTTONDOWN) {

        switch (event.button.button) {
            case SDL_BUTTON_LEFT:
                protocol.attack();
                break;
            case SDL_BUTTON_RIGHT:
                break;
        }


    } else if (event.type == SDL_MOUSEMOTION) {

        double dx = event.motion.x - static_cast<double>(RES_WIDTH) / 2;
        double dy = event.motion.y - static_cast<double>(RES_HEIGTH) / 2;
        double angleInRads = atan2(dy, dx);
        double angleInDegree = 180.0 * angleInRads / M_PI;
        angleInDegree += 90;
        protocol.changeAngle(angleInDegree);
    }
    return true;
}

Coords InputHandler::getMouseCoords() { return mouseCoords; }
