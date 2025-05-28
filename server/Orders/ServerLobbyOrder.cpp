#include "ServerLobbyOrder.h"
#include <stdexcept>
#include <utility>

#include "OrderType.h"
#include "Constants/ProtocolDefaults.h"
#include "Constants/ProtocolContants.h"

ServerLobbyOrder::ServerLobbyOrder(const uint8_t& code, const size_t &clientId)
    : ServerLobbyOrder(code, clientId ,DEFAULT_GAME_NAME, DEFAULT_GAME_MAP_TYPE, DEFAULT_PLAYER_COUNT, DEFAULT_ROUND_COUNT) {}

ServerLobbyOrder::ServerLobbyOrder(const uint8_t& code, const size_t &clientId, const std::string& gameName)
    : ServerLobbyOrder(code, clientId, gameName, DEFAULT_GAME_MAP_TYPE, DEFAULT_PLAYER_COUNT, DEFAULT_ROUND_COUNT) {}


ServerLobbyOrder::ServerLobbyOrder(const uint8_t &code, const size_t &clientId, const std::string &gameName,
                                   const uint8_t &gameMapType, const uint8_t &playerCount, const uint8_t &roundCount)
    : clientId(clientId),  gameName(gameName), mapType(gameMapType), playerCount(playerCount), roundCount(roundCount)  {

    orderTranslator = {
        {ProtocolConstants::GAME_LIST_REQUEST, LOBBY_LIST},
        {ProtocolConstants::JOIN_GAME, LOBBY_JOIN},
        {ProtocolConstants::CREATE_GAME, LOBBY_CREATE},
        {ProtocolConstants::DISCONNECT, LOBBY_DISCONNECT}
    };


    mapTypeTranslator = {
        {MapConstants::DUST,    MapType::DUST},
        {MapConstants::AZTEC_VILLAGE,   MapType::AZTEC_VILLAGE},
        {MapConstants::TRAINING_ZONE,   MapType::TRAINING_ZONE},
        {MapConstants::DUMMY,           MapType::DUMMY}
    };


    orderType = DO_NOTHING;
    if (orderTranslator.contains(code)) {
        orderType = orderTranslator.at(code);
    }

}


ServerLobbyOrder::ServerLobbyOrder(ServerLobbyOrder&& other) noexcept
    : orderType(other.orderType),
      clientId(other.clientId),
      gameName(std::move(other.gameName)),
      mapType(other.mapType),
      playerCount(other.playerCount),
      roundCount(other.roundCount),
      orderTranslator(std::move(other.orderTranslator)),
      mapTypeTranslator(std::move(other.mapTypeTranslator))
{
    other.orderType = DO_NOTHING;
    other.clientId = DEFAULT_CLIENT_ID;
    other.gameName.clear();
    other.mapType = DEFAULT_GAME_MAP_TYPE;
    other.playerCount = DEFAULT_PLAYER_COUNT;
    other.roundCount = DEFAULT_ROUND_COUNT;
    other.orderTranslator.clear();
    other.mapTypeTranslator.clear();
}

ServerLobbyOrder& ServerLobbyOrder::operator=(ServerLobbyOrder&& other) noexcept {
    if (this != &other) {
        orderType = other.orderType;
        clientId = other.clientId;
        gameName = std::move(other.gameName);
        mapType = other.mapType;
        playerCount = other.playerCount;
        roundCount = other.roundCount;
        orderTranslator = std::move(other.orderTranslator);
        mapTypeTranslator = std::move(other.mapTypeTranslator);



        other.orderType = DO_NOTHING;
        other.clientId = DEFAULT_CLIENT_ID;
        other.gameName.clear();
        other.mapType = DEFAULT_GAME_MAP_TYPE;
        other.playerCount = DEFAULT_PLAYER_COUNT;
        other.roundCount = DEFAULT_ROUND_COUNT;
        other.orderTranslator.clear();
        other.mapTypeTranslator.clear();
    }
    return *this;
}

const OrderType& ServerLobbyOrder::getOrderType() const {
    return this->orderTranslator.at(this->orderType);
}

const std::string& ServerLobbyOrder::getGameName() const {
    return this->gameName;
}

const size_t& ServerLobbyOrder::getClientId() const {
    return this->clientId;
}

const MapType& ServerLobbyOrder::getMapType() const {
    return this->mapTypeTranslator.at(this->mapType);
}

const uint8_t& ServerLobbyOrder::getPlayerCount() const {
    return this->playerCount;
}

const uint8_t& ServerLobbyOrder::getRoundCount() const {
    return this->roundCount;
}

