#include "JoinGameFlow.h"

#include "GameFlowUtils.h"
#include "../MessageBox.h"
#include "Login/Dialogs/GameNameDialog.h"

JoinGameFlow::JoinGameFlow(QLineEdit* usernameInput, Protocol& protocol, QWidget* parent, ServerMenu* menu)
        : GameFlowBase(usernameInput, protocol, parent, menu) {}

void JoinGameFlow::run() {
    QString username = getUsername();
    if (username.isEmpty()) return;

    try {
        GameNameDialog nameDialog(parent);
        if (nameDialog.exec() != QDialog::Accepted) return;

        QString gameName = nameDialog.getGameName().trimmed();
        if (gameName.isEmpty()) {
            GameFlowUtils::showError(parent, "⚠️ Invalid Name", "You must enter a valid game name.");
            return;
        }

        GamesList gameList = protocol.getGamesList();
        bool gameExists = false;
        for (const auto& game : gameList.gamesLobbies) {
            if (QString::fromStdString(game.gameName) == gameName) {
                gameExists = true;
                break;
            }
        }

        if (!gameExists) {
            GameFlowUtils::showError(parent, "⚠️ Game Not Found",
                                     QString("The game '%1' does not exist.").arg(gameName));
            return;
        }

        protocol.joinLobby(gameName.toStdString());

        LobbyConnectionDTO lobbyStatus = protocol.getLobbyConnection();
        if (lobbyStatus.status != ConnectionStatus::SUCCESS) {
            GameFlowUtils::showError(parent, "❌ Failed to Join", "Unable to join the selected game lobby.");
            return;
        }

        PlayerChoicesDTO choices = getPlayerChoices();
        showWaitingRoom(username, choices.team, choices.skin);

    } catch (const std::exception& e) {
        GameFlowUtils::showError(parent, "❌ Failed to Join Game",
                                 QString("An unexpected error occurred:\n\n%1").arg(e.what()));
    }
}
