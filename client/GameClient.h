#pragma once

#include "client/GameRenderer.h"
class GameClient {

  bool running;
  GameRenderer gameRenderer;

public:
  GameClient();
  void run();
};
