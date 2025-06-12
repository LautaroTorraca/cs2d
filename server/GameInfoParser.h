//
// Created by lionel on 01/06/25.
//

#ifndef GAMEINFOPARSER_H
#define GAMEINFOPARSER_H
#include <map>
#include <string>

#define TILE_SIZE_KEY "tileSize"
class GameInfoParser {
    std::map<std::string, double> gameInfo;
    std::map<std::string, double> playerInfo;
    std::map<std::string, double> gameMapInfo;

public:
    explicit GameInfoParser(const std::string& gameInfoFilePath);
    GameInfoParser(GameInfoParser&& other) noexcept;
    double getGameInfo(const std::string& key) const;
    double getPlayerInfo(const std::string& key) const;
    double getGameMapInfo(const std::string& key) const;
};


#endif  // GAMEINFOPARSER_H
