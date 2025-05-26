#pragma once

#include <cstdint>
#include <map>
#include "Order.h"
#include "OrderType.h"



class GameLobbyOrder final : public Order {
    OrderType orderType;
    size_t playerId;
    uint8_t teamId;
    uint8_t skinId;

    std::map<uint8_t, OrderType> orderTranslator;

public:
    GameLobbyOrder(const uint8_t& code, const size_t& playerId);
    GameLobbyOrder(const uint8_t& code, const size_t& playerId, const uint8_t& teamId, const uint8_t& skinId);

    GameLobbyOrder(GameLobbyOrder&& other) noexcept;
    GameLobbyOrder& operator=(GameLobbyOrder&& other) noexcept;

    GameLobbyOrder(const GameLobbyOrder&) = delete;
    GameLobbyOrder& operator=(const GameLobbyOrder&) = delete;

    [[nodiscard]] const OrderType& getOrderType() const override;
    [[nodiscard]] const size_t& getPlayerId() const;
    [[nodiscard]] const uint8_t& getTeamId() const;
    [[nodiscard]] const uint8_t& getSkinId() const;

};
