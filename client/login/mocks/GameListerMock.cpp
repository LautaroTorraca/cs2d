#include "GameListerMock.h"
#include <QMessageBox>

QList<GameDTO> GameListerMock::fakeGames() const {
    return {
            { "Match #1", 2, 4 },
            { "Match #2", 1, 15 },
            { "Match #3", 3, 10 }
    };
}

void GameListerMock::showAvailableGames(QWidget* parent) {
    const QList<GameDTO> games = fakeGames();
    QString list = "Available Games:\n\n";

    for (const auto& game : games) {
        list += QString("• %1 — Players: %2/%3 — Rounds: %4\n")
                .arg(game.name)
                .arg(game.playerCount)
                .arg(game.maxPlayers)
                .arg(game.rounds);
    }

    QMessageBox::information(parent, "Available Games", list);
}


QStringList GameListerMock::listGameNames() const {
    QStringList names;
    for (const auto& game : fakeGames()) {
        names << game.name;
    }
    return names;
}
