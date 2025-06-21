#include "CreateGameFlow.h"
#include "GameFlowUtils.h"
#include "../MessageBox.h"
#include "client/Login/Dialogs/MapSelectionDialog.h"
#include <stdexcept>


CreateGameFlow::CreateGameFlow(QLineEdit* usernameInput, Protocol& protocol, QWidget* parent)
        : GameFlowBase(usernameInput, protocol, parent) {}

void CreateGameFlow::run() {
    QString username = getUsername();
    if (username.isEmpty()) return;

    try {
        QString gameName = GameFlowUtils::askGameName(parent);
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
