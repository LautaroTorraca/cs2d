#include "GameLobbyOrder.h"

#include <stdexcept>
#include "Constants/ProtocolDefaults.h"
#include "Constants/ProtocolContants.h"

GameLobbyOrder::GameLobbyOrder(const uint8_t& code, const size_t& playerId)
    : GameLobbyOrder(code, playerId ,DEFAULT_TEAM_ID, DEFAULT_SKIN_ID) {}

GameLobbyOrder::GameLobbyOrder(const uint8_t& code, const size_t& playerId, const uint8_t& teamId, const uint8_t& skinId)
    : playerId(playerId) ,teamId(teamId), skinId(skinId)
{
    orderTranslator = {
        {ProtocolConstants::READY, GAME_LOBBY_READY},
        {ProtocolConstants::EXIT_LOBBY, GAME_LOBBY_EXIT}
    };

    orderType = DO_NOTHING;
    if (orderTranslator.contains(code)) {
        orderType = orderTranslator.at(code);
    }
}

GameLobbyOrder::GameLobbyOrder(GameLobbyOrder&& other) noexcept
    : orderType(other.orderType),
      playerId(other.playerId),
      teamId(other.teamId),
      skinId(other.skinId),
      orderTranslator(std::move(other.orderTranslator))
{
    other.orderType = DO_NOTHING;
    other.playerId = DEFAULT_PLAYER_ID;
    other.teamId = DEFAULT_TEAM_ID;
    other.skinId = DEFAULT_SKIN_ID;
}

GameLobbyOrder& GameLobbyOrder::operator=(GameLobbyOrder&& other) noexcept {
    if (this != &other) {
        orderType = other.orderType;
        playerId = other.playerId;
        teamId = other.teamId;
        skinId = other.skinId;
        orderTranslator = std::move(other.orderTranslator);


        other.orderType = DO_NOTHING;
        other.playerId = DEFAULT_PLAYER_ID;
        other.teamId = DEFAULT_TEAM_ID;
        other.skinId = DEFAULT_SKIN_ID;
    }
    return *this;
}

const OrderType& GameLobbyOrder::getOrderType() const {
    return this->orderType;
}

const size_t& GameLobbyOrder::getPlayerId() const {
    return this->playerId;
}

const uint8_t& GameLobbyOrder::getTeamId() const {
    return this->teamId;
}

const uint8_t& GameLobbyOrder::getSkinId() const {
    return this->skinId;
}
