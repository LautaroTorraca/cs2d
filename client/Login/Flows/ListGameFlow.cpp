#include "ListGameFlow.h"

#include <QStringList>
#include <iostream>
#include <stdexcept>

#include "Login/Dialogs/GameListDialog.h"
#include "Login/Flows/GameFlowUtils.h"
#include "Login/Mappers/MapMapper.h"
#include "Login/MessageBox.h"

ListGameFlow::ListGameFlow(QLineEdit* usernameInput, Protocol& protocol, QWidget* parent, ServerMenu* menu)
        : GameFlowBase(usernameInput, protocol, parent, menu) {}

void ListGameFlow::run() {
    QString username = getUsername();
    if (username.isEmpty()) return;

    try {

        GamesList gameList = protocol.getGamesList();
        if (gameList.gamesLobbies.empty()) {
            GameFlowUtils::showError(parent, "No Games Found", "There are no active games right now.");
            return;
        }

        MapMapper mapMapper;
        QStringList formattedGames;
        for (const auto& game : gameList.gamesLobbies) {
            std::ostringstream oss;
            oss << game.gameName
                << " | Rounds: " << static_cast<int>(game.rounds)
                << " | Map: " << mapMapper.toString(game.mapType).toStdString()
                << " | Max Players: " << static_cast<int>(game.maxPlayers);

            QString entry = QString::fromStdString(oss.str());
            entry.remove('\n');
            entry.remove('\r');
            formattedGames << entry;
        }


        GameListDialog dialog(formattedGames, parent);
        if (dialog.exec() != QDialog::Accepted) return;

        QString selected = dialog.getSelectedGame();
        std::stringstream gameInfo(selected.toStdString());
        std::string gameName;
        gameInfo >> gameName;
        std::cout << gameName << std::endl;
        protocol.joinLobby(gameName);

        LobbyConnectionDTO lobbyStatus = protocol.getLobbyConnection();
        if (lobbyStatus.status != ConnectionStatus::SUCCESS) {
            GameFlowUtils::showError(parent, "Failed to Join", "Unable to join the selected game lobby.");
            return;
        }

        PlayerChoicesDTO choices = getPlayerChoices();
        showWaitingRoom(username, choices.team, choices.skin);

    } catch (const std::exception& e) {
        GameFlowUtils::showError(parent, "Failed to List Games",
                                 QString("An error occurred:\n\n%1").arg(e.what()));
    }
}
