#pragma once

#include <functional>
#include <map>
#include <memory>

#include "Game.h"
#include "GameParser.h"
#include "Orders/InGameOrder.h"

class ServerInGame {
  GameParser gameParser;
  Game game;

  std::map<OrderType, std::function<void(InGameOrder &)>> translator;

  void setupTranslators();

public:
  ServerInGame();

  void handle(const std::unique_ptr<Order> &order) const;
};
