//
// Created by lionel on 01/06/25.
//

#include "GameInfoParser.h"

#include <fstream>

#include <fkYAML/node.hpp>

#define GAME_INFO_KEY "gameInfo"
#define PLAYER_INFO_KEY "playerInfo"
#define GAME_MAP_INFO_KEY "gameMapInfo"

GameInfoParser::GameInfoParser(const std::string& gameInfoFilePath) {
    std::ifstream file(gameInfoFilePath.c_str());
    fkyaml::node root = fkyaml::node::deserialize(file);
    this->gameInfo = root[GAME_INFO_KEY].get_value<std::map<std::string, double>>();
    this->playerInfo = root[PLAYER_INFO_KEY].get_value<std::map<std::string, double>>();
    this->gameMapInfo = root[GAME_MAP_INFO_KEY].get_value<std::map<std::string, double>>();
}

GameInfoParser::GameInfoParser(GameInfoParser&& other) noexcept:
        gameInfo(std::move(other.gameInfo)),
        playerInfo(std::move(other.playerInfo)),
        gameMapInfo(std::move(other.gameMapInfo)) {
    if (this != &other) {
        other.gameInfo = std::map<std::string, double>();
        other.playerInfo = std::map<std::string, double>();
        other.gameMapInfo = std::map<std::string, double>();
    }
}

double GameInfoParser::getGameInfo(const std::string& key) const {
    if (this->gameInfo.contains(key)) {
        return this->gameInfo.at(key);
    }
    return 0.0;
}

double GameInfoParser::getPlayerInfo(const std::string& key) const {
    if (this->playerInfo.contains(key)) {
        return this->playerInfo.at(key);
    }
    return 0.0;
}

double GameInfoParser::getGameMapInfo(const std::string& key) const {
    if (this->gameMapInfo.contains(key)) {
        return this->gameMapInfo.at(key);
    }
    return 0.0;
}
