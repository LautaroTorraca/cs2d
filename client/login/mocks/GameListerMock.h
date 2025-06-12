#pragma once

#include "GameDTO.h"
#include <QList>
#include <QStringList>
#include <QWidget>

class GameListerMock {
public:
    void showAvailableGames(QWidget* parent);
    QStringList listGameNames() const;

    QList<GameDTO> fakeGames() const;
};
