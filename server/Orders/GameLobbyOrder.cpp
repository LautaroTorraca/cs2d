#include "GameLobbyOrder.h"

#include <stdexcept>

#include "common/Constants/ProtocolContants.h"
#include "server/Constants/ProtocolDefaults.h"

GameLobbyOrder::GameLobbyOrder(const uint8_t &code, const size_t &playerId)
    : GameLobbyOrder(code, playerId, DEFAULT_GAME_NAME, DEFAULT_TEAM_ID, DEFAULT_SKIN_ID) {}

GameLobbyOrder::GameLobbyOrder(const uint8_t &code, const size_t &playerId, const std::string& playerName,
                               const uint8_t &teamId, const uint8_t &skinId)
    : playerId(playerId), playerName(playerName), teamId(teamId), skinId(skinId) {
  orderTranslator = {{ProtocolConstants::READY, GAME_LOBBY_READY},
                     {ProtocolConstants::EXIT_LOBBY, GAME_LOBBY_EXIT}};

  teamTranslator = {{TeamConstants::TERRORISTS, TERRORISTS},
                    {TeamConstants::COUNTER_TERRORISTS, COUNTER_TERRORISTS}};

  skinTranslator = {// Terrorist skins
                    {SkinConstants::PHOENIX, PHOENIX},
                    {SkinConstants::L337_KREW, L337_KREW},
                    {SkinConstants::ARCTIC_AVENGER, ARCTIC_AVENGER},
                    {SkinConstants::GUERRILLA, GUERRILLA},

                    // Counter-Terrorist skins
                    {SkinConstants::SEAL_FORCE, SEAL_FORCE},
                    {SkinConstants::GERMAN_GSG9, GERMAN_GSG9},
                    {SkinConstants::UK_SAS, UK_SAS},
                    {SkinConstants::FRENCH_GIGN, FRENCH_GIGN}};

  orderType = DO_NOTHING;
  if (orderTranslator.contains(code)) {
    orderType = orderTranslator.at(code);
  }
}

GameLobbyOrder::GameLobbyOrder(GameLobbyOrder &&other) noexcept
    : orderType(other.orderType), playerId(other.playerId), playerName(other.playerName),
      teamId(other.teamId), skinId(other.skinId),
      orderTranslator(std::move(other.orderTranslator)), teamTranslator(std::move(other.teamTranslator)), skinTranslator(std::move(other.skinTranslator)) {
  other.orderType = DO_NOTHING;
  other.playerId = DEFAULT_PLAYER_ID;
    other.playerName = "";
  other.teamId = DEFAULT_TEAM_ID;
  other.skinId = DEFAULT_SKIN_ID;
    other.orderTranslator = std::map<uint8_t, OrderType>();
    other.skinTranslator = std::map<uint8_t, Skin>();
    other.teamTranslator = std::map<uint8_t, Team>();
}

GameLobbyOrder &GameLobbyOrder::operator=(GameLobbyOrder &&other) noexcept {
  if (this != &other) {
    orderType = other.orderType;
    playerId = other.playerId;
      playerName = other.playerName;
    teamId = other.teamId;
    skinId = other.skinId;
    orderTranslator = std::move(other.orderTranslator);
      skinTranslator = std::move(other.skinTranslator);
      teamTranslator = std::move(other.teamTranslator);

    other.orderType = DO_NOTHING;
    other.playerId = DEFAULT_PLAYER_ID;
    other.teamId = DEFAULT_TEAM_ID;
    other.skinId = DEFAULT_SKIN_ID;
      other.orderTranslator = std::map<uint8_t, OrderType>();
      other.skinTranslator = std::map<uint8_t, Skin>();
      other.teamTranslator = std::map<uint8_t, Team>();
  }
  return *this;
}

const OrderType &GameLobbyOrder::getOrderType() const {
  return this->orderTranslator.at(this->orderType);
}

const size_t &GameLobbyOrder::getPlayerId() const { return this->playerId; }

const std::string & GameLobbyOrder::getPlayerName() const {
  return this->playerName;
}

const Team &GameLobbyOrder::getTeamId() const {
  return this->teamTranslator.at(this->teamId);
}

const Skin &GameLobbyOrder::getSkinId() const {
  return this->skinTranslator.at(this->skinId);
}
