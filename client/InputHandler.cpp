#include "InputHandler.h"

#include <iostream>

#include "Constants/ClientConstants.h"
#include "Constants/PlayerDataConstants.h"
#include "server/GameStatus.h"
#include "server/ProductType.h"

#include "MoveConstants.h"
#include "SDL_events.h"
#include "SDL_keycode.h"

InputHandler::InputHandler(Protocol& protocol): protocol(protocol) {}

bool InputHandler::processEvents(SDL_Event& event, GameStatus status) {

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
                        break;
                    case SDLK_s:
                        protocol.move(Down);
                        break;
                    case SDLK_a:
                        protocol.move(Left);
                        break;
                    case SDLK_d:
                        protocol.move(Right);
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
        } catch (...) {
            std::cout << "catcheo el error en inputHandler\n\n" << "\n\n";
            return false;
        }
    } while (SDL_PollEvent(&event));

    return true;
}
Coords InputHandler::getMouseCoords() { return mouseCoords; }
bool InputHandler::isInMenu() { return inBuyMenu; }
