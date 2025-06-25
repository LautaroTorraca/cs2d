#include "GameClient.h"

#include <iostream>
// #include <utility>

#include <bits/types/error_t.h>
#include <qapplication.h>
#include <qdialog.h>

#include "common/Constants/MapTypeConstants.h"
#include "client/GameRenderer.h"

#include "InputHandler.h"
#include "SDL_timer.h"
#include "fixedOverWritingQueue.h"
using std::stringstream;

using namespace SDL2pp;
using namespace DTO;


GameClient::GameClient(Protocol& protocol):
        running(true),
        protocol(protocol),
        inputHandler(protocol),
        dataReceiver(protocol, snapshotQueue),
        parser("../settings.yaml") {}


void GameClient::run(const MapType& mapType) {

    double res_width = parser.getResolution("resolution_width");
    double res_height = parser.getResolution("resolution_height");

    PreSnapshot preSnapshot = protocol.receivePreSnapshot();
    GameRenderer renderer(preSnapshot.map, preSnapshot.clientId, res_width, res_height,
                          preSnapshot.shopInfo);

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

                running = inputHandler.processEvents(event, gameSnapshot.status, res_width,
                                                     res_height);


                running = renderer.setScreen(gameSnapshot, mapType, inputHandler.getMouseCoords());


                if (inputHandler.isInMenu()) {
                    renderer.setBuyMenu();
                }
                renderer.render();
                frameStart = SDL_GetTicks();
            }
            SDL_Delay(10);
        }
    } catch (...) {
    }
    dataReceiver.close();
    dataReceiver.join();
}
