#include "GameClient.h"

#include <iostream>

#include <bits/types/error_t.h>
#include <qapplication.h>
#include <qdialog.h>

#include "client/GameRenderer.h"
#include "server/Constants/MapTypeConstants.h"

#include "InputHandler.h"
#include "Protocol.h"
#include "SDL_timer.h"
#include "fixedOverWritingQueue.h"

using namespace Client;
using std::stringstream;

using namespace SDL2pp;
using namespace DTO;

// TODO: sonido.
// TODO: armas en la mano.
// TODO: cuchillazos.
// TODO: BOMBA -- ver como pasar las imagnes por tiempo
// TODO: moviemiento de personaje.
// TODO: tiros mas facheros.
// TODO: MENU.
// TODO: movimiento simulateno. a chequear.
// TODO: terminar UI. Cuadros y colores.

GameClient::GameClient(Protocol& protocol):
        running(true),
        protocol(protocol),
        inputHandler(protocol),
        dataReceiver(protocol, snapshotQueue) {}

void GameClient::run() {

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
