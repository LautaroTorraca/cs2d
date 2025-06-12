#include "GameClient.h"

#include <iostream>
#include <sstream>

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
// #include "MainWindow.h"
// #include "Protocol.h"
#include "SDL_timer.h"

using std::stringstream;

using namespace SDL2pp;
using namespace DTO;

GameClient::GameClient(char* port):
        running(true), protocol(HOSTNAME, port), inputHandler(protocol) {}

void GameClient::run(int argc, char* argv[]) {
    //
    // QApplication app(argc, argv);
    // MainWindow mainMenu;
    // if (mainMenu.exec() == QDialog::Accepted) {
    //     ConnectionChoice choice = mainMenu.getChoice();
    //
    //     switch (choice) {
    //         case ConnectionChoice::None: {
    //             std::cout << "nada\n";
    //             break;
    //         }
    //         case ConnectionChoice::Create: {
    //             std::cout << "crear\n";
    //             break;
    //         }
    //         case ConnectionChoice::Join: {
    //
    //             std::cout << "unirse\n";
    //             break;
    //         }
    //     }
    // }
    std::cout << "hasta aca todo joya no?\n";
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
                // FIX: cambiar harcodeada de mapa.
                renderer.renderScreen(protocol.receiveSnapshot(), MapType::DUST,
                                      inputHandler.getMouseCoords());
                frameStart = SDL_GetTicks();
            }
        }
    }
}
