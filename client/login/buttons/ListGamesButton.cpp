#include "ListGamesButton.h"
#include "../MessageBox.h"
#include "../dialogs/GameListDialog.h"
#include "../mocks/GameListerMock.h"
#include "../MapTraslator.h"

ListGamesButton::ListGamesButton(QWidget* parent)
        : GameMenuButton("☰ List Games", parent) {
    connect(this, &QPushButton::clicked, this, &ListGamesButton::handleClick);
}

void ListGamesButton::handleClick() {
    QWidget* parentWindow = this->parentWidget();

    if (!parentWindow) {
        MessageBox msg(this);
        msg.showMessage("Internal Error",
                        "Unable to determine parent window to display the list.",
                        MessageType::Error);
        return;
    }

    try {
        GameListerMock lister;
        QList<GameDTO> games = lister.fakeGames();

        if (games.isEmpty()) {
            MessageBox msg(this);
            msg.showMessage("No Games Found",
                            "There are no games available at the moment.",
                            MessageType::Info);
            return;
        }

        QStringList formattedGames;
        MapMapper mapMapper;

        for (const auto& game : games) {
            QString line = QString("• %1 — %2/%3 players — %4 — %5 rounds")
                    .arg(game.name)
                    .arg(game.playerCount)
                    .arg(game.maxPlayers)
                    .arg(mapMapper.toString(game.mapType))
                    .arg(game.rounds);
            formattedGames << line;
        }

        GameListDialog dialog(formattedGames, parentWindow);
        if (dialog.exec() == QDialog::Accepted) {
            QString selected = dialog.getSelectedGame();
            MessageBox msg(this);
            msg.showMessage("Game Selected", QString("You selected <b>%1</b>.").arg(selected), MessageType::Success);

            // TODO: conectar con flujo de join real
        }

    } catch (const std::exception& e) {
        MessageBox msg(this);
        msg.showMessage("Failed to List Games",
                        QString("An error occurred while listing games:\n\n%1").arg(e.what()),
                        MessageType::Error);
    }
}
