#include <QMessageBox>
#include "GameListerMock.h"
#include "../MapTraslator.h"

QList<GameDTO> GameListerMock::fakeGames() const {
    return {
            GameDTO("Match #1", MapType::DUST, 2, 4, 12),
            GameDTO("Match #2", MapType::AZTEC_VILLAGE, 3, 6, 8),
            GameDTO("Match #3", MapType::TRAINING_ZONE, 1, 10, 20)
    };
}

void GameListerMock::showAvailableGames(QWidget* parent) {
    const QList<GameDTO> games = fakeGames();
    MapMapper mapMapper;

    QString list = "Available Games:\n\n";
    for (const auto& game : games) {
        list += QString("• %1 — %2/%3 players — %4 — %5 rounds\n")
                .arg(game.name)
                .arg(game.playerCount)
                .arg(game.maxPlayers)
                .arg(mapMapper.toString(game.mapType))
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
