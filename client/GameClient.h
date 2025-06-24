#pragma once
#include <string>
// #include <thread>

#include "DataReceiver.h"
#include "InputHandler.h"
#include "Protocol.h"
#include "SettingsParser.h"

constexpr std::string PORT = "8080";
constexpr std::string HOSTNAME = "127.0.0.1";
// #include "client/GameRenderer.h"

class GameClient {
    bool running;
    QueueFixed<Snapshot> snapshotQueue;
    Protocol protocol;
    InputHandler inputHandler;
    DataReceiver dataReceiver;
    SettingsParser parser;

public:
    GameClient(char* port);
    GameClient(Protocol& protocol);
    void run(int argc, char* argv[]);
    void run();
};
