#include "GameClient.h"

#include <iostream>
// #include <utility>

#include <bits/types/error_t.h>
#include <qapplication.h>
#include <qdialog.h>

#include "client/GameRenderer.h"
#include "server/Constants/MapTypeConstants.h"

#include "InputHandler.h"
#include "MainWindow.h"
#include "SDL_timer.h"
#include "fixedOverWritingQueue.h"
using std::stringstream;

using namespace SDL2pp;
using namespace DTO;

// TODO: sonido.
// TODO: cuchillazos.
// TODO: movimiento simulateno. a chequear.
// TODO: tiros mas facheros.
// TODO: MENU masomenos
// TODO: terminar UI. Cuadros y colores.

// NOTE: refactorizar codigo.....

GameClient::GameClient(Protocol& protocol):
        running(true),
        protocol(HOSTNAME, PORT),
        inputHandler(protocol),
        dataReceiver(protocol, snapshotQueue) {}

GameClient::GameClient(char* port):
        running(true),
        protocol(HOSTNAME, port),
        inputHandler(protocol),
        dataReceiver(protocol, snapshotQueue) {}

void GameClient::run() {}
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
                LobbyDTO lobby("hola", MapType::DUST, 2, 6);
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

    // HACK: fix constant loop rate.
    PreSnapshot preSnapshot = protocol.receivePreSnapshot();
    GameRenderer renderer(preSnapshot.map, preSnapshot.clientId);
    try {
        dataReceiver.start();
        bool running = true;
        const int FPS = 60;
        const int frameDelay = 1000 / FPS;
        uint32_t frameStart = SDL_GetTicks();
        int frameTime;
        SDL sdl(SDL_INIT_VIDEO);


        while (running) {
            SDL_Event event;
            frameTime = SDL_GetTicks() - frameStart;


            if (frameDelay <= frameTime) {
                Snapshot gameSnapshot = snapshotQueue.pop();

                running = inputHandler.processEvents(event, gameSnapshot.status);
                // FIX: cambiar harcodeada de mapa.
                // HACK: tambien sacar el maptype como argumento, que entre cuando se crea el
                // renderer.

                renderer.setScreen(gameSnapshot, MapType::DUST, inputHandler.getMouseCoords());
                if (inputHandler.isInMenu()) {
                    renderer.setBuyMenu();
                }
                renderer.render();
                frameStart = SDL_GetTicks();
            }
            SDL_Delay(10);
        }
    } catch (...) {
        std::cout << "catcheo en gameClient\n\n";
    }
    protocol.exit();
    dataReceiver.close();
    dataReceiver.join();
}
