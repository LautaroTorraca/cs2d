#pragma once

#include "Constants/MapTypeConstants.h"
#include "Order.h"
#include "OrderType.h"
#include <map>
#include <string>

class ServerLobbyOrder final : public Order {
  OrderType orderType;
  size_t clientId;
  std::string gameName;
  uint8_t mapType;
  uint8_t playerCount;
  uint8_t roundCount;

  std::map<uint8_t, OrderType> orderTranslator;
  std::map<uint8_t, MapType> mapTypeTranslator;

public:
  ServerLobbyOrder(const uint8_t &code, const size_t &clientId);
  ServerLobbyOrder(const uint8_t &code, const size_t &clientId,
                   const std::string &gameName);
  ServerLobbyOrder(const uint8_t &code, const size_t &clientId,
                   const std::string &gameName, const uint8_t &gameMapType,
                   const uint8_t &playerCount, const uint8_t &roundCount);

  ServerLobbyOrder(ServerLobbyOrder &&other) noexcept;
  ServerLobbyOrder &operator=(ServerLobbyOrder &&other) noexcept;

  ServerLobbyOrder(const ServerLobbyOrder &) = delete;
  ServerLobbyOrder &operator=(const ServerLobbyOrder &) = delete;

  [[nodiscard]] const OrderType &getOrderType() const override;
  [[nodiscard]] const std::string &getGameName() const;
  const size_t &getClientId() const;
  const MapType &getMapType() const;
  const uint8_t &getPlayerCount() const;
  const uint8_t &getRoundCount() const;
};
