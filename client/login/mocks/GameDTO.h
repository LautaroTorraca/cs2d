#ifndef GAME_DTO_H
#define GAME_DTO_H

#include <QString>

class GameDTO {
public:
    QString name;
    int playerCount = 0;
    int maxPlayers = 0;
    int rounds = 0;
};

#endif
