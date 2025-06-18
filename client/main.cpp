// TODO: ver QT para el menu.
#include <exception>
#include <iostream>
#include <QApplication>
#include "login/ServerMenu.h"

#include "GameClient.h"
// #include "SDL_events.h"
// #include "gameConstants.h"
// #include "_deps/sdl2_image-src/include/SDL_image.h"
// #include "common/Constants/PlayerInformationConstants.h"
// #include "gameConstants.h"

#include <SDL2/SDL.h>
#include <build/_deps/libsdl2pp-src/SDL2pp/SDL2pp.hh>

using namespace DTO;
// #include "weaponConstants.h"

// TODO: cono de luz

int main(int argc, char* argv[]) {
    try {
        // QApplication app();  // 💥 SIEMPRE antes que cualquier QWidget
        //                      //
        GameClient game(argv[1]);
        game.run(argc, argv);
        return 0;

    } catch (std::exception& e) {

        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
