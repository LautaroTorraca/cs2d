#include "ListGameFlow.h"
#include "Login/Dialogs/GameListDialog.h"
#include "Login/MessageBox.h"
#include "Login/Flows/GameFlowUtils.h"

#include <QStringList>
#include <stdexcept>

ListGameFlow::ListGameFlow(QLineEdit* usernameInput, Protocol& protocol, QWidget* parent, ServerMenu* menu)
        : GameFlowBase(usernameInput, protocol, parent, menu) {}

void ListGameFlow::run() {
    QString username = getUsername();
    if (username.isEmpty()) return;

    try {
        GamesList gameList = protocol.getGamesList();
        if (gameList.games.empty()) {
            GameFlowUtils::showError(parent, "No Games Found", "There are no active games right now.");
            return;
        }

        QStringList formattedGames;
        for (const std::string& game : gameList.games) {
            QString clean = QString::fromStdString(game);
            clean.remove('\n');
            clean.remove('\r');
            formattedGames << clean;
        }

        GameListDialog dialog(formattedGames, parent);
        if (dialog.exec() != QDialog::Accepted) return;

        QString selected = dialog.getSelectedGame();

        protocol.joinLobby(selected.toStdString());

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
