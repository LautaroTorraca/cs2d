#include "GameClient.h"

#include <iostream>
#include <sstream>

#include <qapplication.h>
#include <qdialog.h>

#include "client/GameRenderer.h"
// #include "server/Constants/ConnectionStatus.h"
#include "server/Constants/MapTypeConstants.h"
// #include "server/DTO/GameLobbyDTO.h"
#include "server/DTO/LobbyConnectionDTO.h"
// #include "server/DTO/LobbyConnectionDTO.h"
// #include "server/DTO/PlayerChoicesDTO.h"
// #include "server/Team.h"

#include "InputHandler.h"
#include "MainWindow.h"
#include "Protocol.h"
#include "SDL_timer.h"

using std::stringstream;

using namespace SDL2pp;
using namespace DTO;

GameClient::GameClient(char* port):
        running(true), protocol(HOSTNAME, port), inputHandler(protocol) {}

void GameClient::run(int argc, char* argv[]) {

    QApplication app(argc, argv);
    MainWindow mainMenu;
    if (mainMenu.exec() == QDialog::Accepted) {
        ConnectionChoice choice = mainMenu.getChoice();

        switch (choice) {
            case ConnectionChoice::None: {
                std::cout << "nada\n";
                break;
            }
            case ConnectionChoice::Create: {
                std::cout << "crear\n";
                LobbyDTO lobby("hola", MapType::DUST, 2, 2);
                protocol.createLobby(lobby);
                std::cout << "aca llego=?\n\n";
                LobbyConnectionDTO lobbyStatus = protocol.getLobbyConnection();
                std::cout << "lobbyStatus, id: " << lobbyStatus.id
                          << ", status: " << (int)lobbyStatus.status << std::endl;
                if (lobbyStatus.status == ConnectionStatus::SUCCESS) {
                    std::cout << "se creo el lobby correctamente\n";
                } else {
                    std::cout << "fallo xd\n";
                }
                PlayerChoicesDTO playerChoices(1234, "jorge", Team::TERRORISTS, Skin::PHOENIX);
                protocol.ready(playerChoices);
                GameLobbyDTO gameLobby = protocol.getGameLobby();
                while (gameLobby.status != READY_STATUS) {
                    std::cout << "todavia no se creo el game correctamente\n";
                    gameLobby = protocol.getGameLobby();
                }
                std::cout << "Se creo el game correctamente\n";
                break;
            }
            case ConnectionChoice::Join: {

                std::cout << "unirse\n";
                LobbyDTO lobby("hola");
                protocol.joinLobby(lobby);
                LobbyConnectionDTO lobbyStatus = protocol.getLobbyConnection();
                if (lobbyStatus.status == ConnectionStatus::SUCCESS) {
                    std::cout << "se creo el lobby correctamente\n";
                } else {
                    std::cout << "fallo xd\n";
                }
                PlayerChoicesDTO playerChoices(4321, "pablo", Team::COUNTER_TERRORISTS,
                                               Skin::UK_SAS);
                protocol.ready(playerChoices);
                GameLobbyDTO gameLobby = protocol.getGameLobby();
                while (gameLobby.status != READY_STATUS) {
                    std::cout << "todavia no se creo el game correctamente\n";
                    GameLobbyDTO gameLobby = protocol.getGameLobby();
                }
                std::cout << "Se creo el game correctamente\n";
                break;
            }
        }
    }
    std::cout << "hasta aca todo joya no?\n";
    //   //////////
    //
    //   std::string line;
    //   std::string command;
    //   std::getline(std::cin, line);
    //
    //   stringstream ss(line);
    //   ss >> command;
    //   if (command == "crear") {
    //       LobbyDTO lobby("partida1", MapType::DUST, 2, 10);
    //       protocol.createLobby(lobby);
    //       PlayerChoicesDTO playerChoices(1234, "jorge", Team::TERRORISTS, Skin::GERMAN_GSG9);
    //       SDL_Delay(10000);
    //       protocol.ready(playerChoices);
    //   } else {
    //
    //       LobbyDTO lobby("partida1");
    //       protocol.joinLobby(lobby);
    //       PlayerChoicesDTO playerChoices(1432, "blackri", Team::COUNTER_TERRORISTS,
    //       Skin::UK_SAS); protocol.ready(playerChoices);
    //   }
    //   ////
    // TODO: menu QT

    PreSnapshot preSnapshot = protocol.receivePreSnapshot();
    GameRenderer renderer(preSnapshot.map, preSnapshot.clientId);

    bool running = true;
    const int FPS = 1000;
    const int frameDelay = 1000 / FPS;
    uint32_t frameStart = SDL_GetTicks();
    int frameTime;
    SDL sdl(SDL_INIT_VIDEO);

    while (running) {
        // gameSnapshot = protocol.receiveSnapshot();
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            running = inputHandler.processEvent(event);
        }
        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay <= frameTime) {
            // FIX: cambiar harcodeada de mapa.
            std::cout << "GameClient::run, sigo adentro." << std::endl;
            renderer.renderScreen(protocol.receiveSnapshot(), MapType::DUST,
                                  inputHandler.getMouseCoords());
            frameStart = SDL_GetTicks();
        }

    }
}
