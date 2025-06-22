#include "JoinGameFlow.h"

#include "GameFlowUtils.h"
#include "../MessageBox.h"
#include "client/Login/Dialogs/GameListDialog.h"



JoinGameFlow::JoinGameFlow(QLineEdit* usernameInput, Protocol& protocol, QWidget* parent)
        : GameFlowBase(usernameInput, protocol, parent) {}

void JoinGameFlow::run() {
    QString username = getUsername();
    if (username.isEmpty()) return;

    try {
        GamesList gameList = protocol.getGamesList();
        QStringList qGames;
        for (const auto& game : gameList.gamesLobbies) {
            qGames.append(QString::fromStdString(game.gameName));
        }

        GameListDialog listDialog(qGames, parent);
        int result = listDialog.exec();
        if (result != QDialog::Accepted)
            return;

        QString gameName = listDialog.getSelectedGame();
        protocol.joinLobby(gameName.toStdString());

        LobbyConnectionDTO lobbyStatus = protocol.getLobbyConnection();
        if (lobbyStatus.status != ConnectionStatus::SUCCESS) {
            GameFlowUtils::showError(parent, "Failed to Join", "Unable to join the selected game lobby.");
            return;
        }

        PlayerChoicesDTO choices = getPlayerChoices();
        showWaitingRoom(username, choices.team, choices.skin);

    } catch (const std::exception& e) {
        GameFlowUtils::showError(parent, "❌ Failed to Join Game",
                                 QString("An unexpected error occurred:\n\n%1").arg(e.what()));
    }
}

