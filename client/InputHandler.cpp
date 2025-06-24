#include "InputHandler.h"

#include <iostream>

#include "Constants/PlayerDataConstants.h"
#include "server/GameStatus.h"
#include "server/ProductType.h"

#include "MoveConstants.h"
#include "SDL_events.h"
#include "SDL_keycode.h"

InputHandler::InputHandler(Protocol& protocol): protocol(protocol) {}

bool InputHandler::processEvents(SDL_Event& event, GameStatus status, double res_w, double res_h) {

    do {
        if (status != GameStatus::BUY_TIME)
            inBuyMenu = false;

        try {
            if (event.type == SDL_QUIT) {
                return false;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_b:
                        if (status == GameStatus::BUY_TIME)
                            inBuyMenu = !inBuyMenu;
                        break;
                    case SDLK_w:
                        protocol.move(Up);
                        checkDiagonalMovement();
                        break;
                    case SDLK_s:
                        protocol.move(Down);
                        checkDiagonalMovement();
                        break;
                    case SDLK_a:
                        protocol.move(Left);
                        checkDiagonalMovement();
                        break;
                    case SDLK_d:
                        protocol.move(Right);
                        checkDiagonalMovement();
                        break;
                    case SDLK_1:
                        if (inBuyMenu)
                            protocol.buy({ProductType::AK_47_WEAPON, 1});
                        else
                            protocol.changeWeapon(0);
                        break;
                    case SDLK_2:
                        if (inBuyMenu)
                            protocol.buy({ProductType::M3_WEAPON, 1});
                        else
                            protocol.changeWeapon(1);
                        break;
                    case SDLK_3:
                        if (inBuyMenu)
                            protocol.buy({ProductType::AWP_WEAPON, 1});
                        else
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
                    case SDLK_9:
                        if (inBuyMenu)
                            protocol.buy({ProductType::PRIMARY_AMMO, 5});
                        break;
                    case SDLK_0:
                        if (inBuyMenu)
                            protocol.buy({ProductType::SECONDARY_AMMO, 5});
                        break;
                    case SDLK_ESCAPE:
                        protocol.exit();
                }
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {

                switch (event.button.button) {
                    case SDL_BUTTON_LEFT: {
                        protocol.attack();
                        break;
                    }
                    case SDL_BUTTON_RIGHT:
                        break;
                }
            } else if (event.type == SDL_MOUSEMOTION) {

                double dx = event.motion.x - static_cast<double>(res_w) / 2;
                double dy = event.motion.y - static_cast<double>(res_h) / 2;
                double angleInRads = atan2(dy, dx);
                double angleInDegree = 180.0 * angleInRads / M_PI;
                angleInDegree += 90;
                protocol.changeAngle(angleInDegree);
            }
        } catch (...) {
            std::cout << "catcheo el error en inputHandler\n\n" << "\n\n";
            return false;
        }
    } while (SDL_PollEvent(&event));

    return true;
}
Coords InputHandler::getMouseCoords() { return mouseCoords; }
bool InputHandler::isInMenu() { return inBuyMenu; }

void InputHandler::checkDiagonalMovement() {
    const Uint8* keyState = SDL_GetKeyboardState(NULL);

    if (keyState[SDL_SCANCODE_W])
        protocol.move(Up);
    if (keyState[SDL_SCANCODE_S])
        protocol.move(Down);
    if (keyState[SDL_SCANCODE_A])
        protocol.move(Left);
    if (keyState[SDL_SCANCODE_D])
        protocol.move(Right);
}
