#include "CreateGameFlow.h"

#include <stdexcept>

#include "../MessageBox.h"
#include "Login/Dialogs/MapSelectionDialog.h"
#include "Login/ServerMenu.h"
#include "Login/Audio/MusicManager.h"

#include "GameFlowUtils.h"

CreateGameFlow::CreateGameFlow(QLineEdit* usernameInput, Protocol& protocol, QWidget* parent, ServerMenu* menu)
        : GameFlowBase(usernameInput, protocol, parent, menu) {}

void CreateGameFlow::run() {
    QString username = getUsername();
    if (username.isEmpty()) return;

    try {
        QString gameName = GameFlowUtils::askGameName(parent).trimmed();
        if (gameName.isEmpty()) {
            GameFlowUtils::showError(parent, "⚠️ Invalid Name", "You must enter a valid game name.");
            return;
        }

        MapType map = GameFlowUtils::askMap(parent);
        auto config = GameFlowUtils::askConfig(parent);

        LobbyDTO lobbyDto(gameName.toStdString(), map, config.first, config.second);
        protocol.createLobby(lobbyDto);

        LobbyConnectionDTO lobbyStatus = protocol.getLobbyConnection();
        if (lobbyStatus.status != ConnectionStatus::SUCCESS)
            return;

        PlayerChoicesDTO choices = getPlayerChoices();
        showWaitingRoom(username, choices.team, choices.skin);

    } catch (const std::exception& e) {
        GameFlowUtils::showError(parent, "❌ Failed to Create Game",
                                 QString("An unexpected error occurred:\n\n%1").arg(e.what()));
    }
}
