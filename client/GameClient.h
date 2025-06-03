#pragma once
#include "InputHandler.h"

#include "Protocol.h"

#include <string>

constexpr std::string PORT = "8080";
constexpr std::string HOSTNAME = "127.0.0.1";
// #include "client/GameRenderer.h"

class GameClient {
  bool running;
  Protocol protocol;
  InputHandler inputHandler;
  // GameRenderer gameRenderer;

public:
  GameClient();
  void run();
};
