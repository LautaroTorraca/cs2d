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
<<<<<<< HEAD
  ServerInGame();

  void handle(const std::unique_ptr<Order> &order) const;
=======
    explicit ServerInGame(InGameProtocolInterface& protocol);
    void handle(const std::unique_ptr<Order>& order) const;
    void addNewGame(std::string& gameName, const GameLobbyDTO& gameInfo);
>>>>>>> 80705a0 (Agregando CMakeList del server configurado y solucionando errores de compilacion del server)
};
