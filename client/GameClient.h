#pragma once
#include <string>
#include <thread>

#include "InputHandler.h"
#include "Protocol.h"
// #include "Protocol_testing.h"

constexpr std::string PORT = "8080";
constexpr std::string HOSTNAME = "127.0.0.1";
// #include "client/GameRenderer.h"

class GameClient {
    bool running;
    Protocol protocol;
    InputHandler inputHandler;
    // GameRenderer gameRenderer;

public:
    GameClient(char* port);
    void run(int argc, char* argv[]);
};
