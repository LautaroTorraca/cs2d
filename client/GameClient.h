#pragma once
#include <string>
// #include <thread>

#include "DataReceiver.h"
#include "InputHandler.h"
#include "Protocol.h"

constexpr std::string PORT = "8080";
constexpr std::string HOSTNAME = "127.0.0.1";
// #include "client/GameRenderer.h"

class GameClient {
    bool running;
    QueueFixed<Snapshot> snapshotQueue;
    Protocol protocol;
    InputHandler inputHandler;
    DataReceiver dataReceiver;

public:
    GameClient(char* port);
    void run(int argc, char* argv[]);
};
