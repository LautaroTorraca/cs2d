#ifndef GAME_CREATOR_MOCK_H
#define GAME_CREATOR_MOCK_H

#include "GameDTO.h"
#include <QWidget>

class GameCreatorMock {
public:
    GameDTO openCreateGameDialog(QWidget *parent);
};

#endif
