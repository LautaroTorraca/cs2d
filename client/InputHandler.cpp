#include "InputHandler.h"

#include <iostream>

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
            case SDLK_e:
                protocol.pickUp();
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
            case SDLK_COMMA:
                protocol.buy({ProductTypes::PRIMARY_AMMO, 5});
                break;
            case SDLK_PERIOD:
                protocol.buy({ProductTypes::SECONDARY_AMMO, 5});
                break;
            case SDLK_ESCAPE:
                protocol.exit();
        }
        return true;
    } catch (...) {
        std::cout << "catcheo el error en inputHandler\n\n" << "\n\n";
        return false;
    }
}

Coords InputHandler::getMouseCoords() { return mouseCoords; }
