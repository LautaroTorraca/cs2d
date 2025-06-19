#include "CreateGameButton.h"

#include "../MessageBox.h"
#include "../SkinTraslator.h"
#include "client/LobbyDTO.h"
#include "login/dialogs/CreateGameDialog.h"
#include "login/dialogs/GameNameDialog.h"
#include "login/dialogs/MapSelectionDialog.h"
#include "login/dialogs/SkinSelectionDialog.h"
#include "login/dialogs/TeamSelectionDialog.h"
#include "login/dialogs/WaitingRoomDialog.h"
#include "server/Team.h"

#include <iostream>
#include <stdexcept>

CreateGameButton::CreateGameButton(QWidget* parent, QLineEdit* usernameInput, Protocol& protocol)
        : GameMenuButton("➕  Create Game", parent), usernameInput(usernameInput), protocol(protocol) {
    connect(this, &QPushButton::clicked, this, &CreateGameButton::handleClick);
}

void CreateGameButton::handleClick() {
    QWidget* parent = this->parentWidget();
    QString name = selectUsername();
    if (name.isEmpty()) return;

    try {
        QString gameName = selectGameName(parent);
        MapType map = selectMap(parent);
        std::pair<uint8_t, uint8_t> config = selectConfig(parent);
        uint8_t teamId = selectTeam(parent);
        uint8_t skinId = selectSkin(teamId, parent);

        LobbyDTO lobbyDto(gameName.toStdString(), map, config.first, config.second);
        protocol.createLobby(lobbyDto);

        LobbyConnectionDTO lobbyStatus = protocol.getLobbyConnection();
        if (lobbyStatus.status != ConnectionStatus::SUCCESS) {
            std::cerr << "Fail to connect to the server menu \n";
            return;
        }

        PlayerChoicesDTO playerChoices(name.toStdString(),
                                       static_cast<Team>(teamId),
                                       static_cast<Skin>(skinId));

        QString teamName;
        if (teamId == Team::COUNTER_TERRORISTS) {
            teamName = "CT";
        } else {
            teamName = "T";
        }

        showWaitingRoom(name, teamName, skinId, parent);

    } catch (const std::exception& e) {
        MessageBox msg(this);
        msg.showMessage("❌ Failed to Create Game",
                        QString("An unexpected error occurred:\n\n%1").arg(e.what()),
                        MessageType::Error);
    }
}

QString CreateGameButton::selectUsername() {
    QString name = usernameInput->text().trimmed();
    if (name.isEmpty()) {
        MessageBox msg(this);
        msg.showMessage("Name Required", "Please enter your name to continue.", MessageType::Warning);
    }
    return name;
}

QString CreateGameButton::selectGameName(QWidget* parent) {
    GameNameDialog dialog(parent, "Enter a name for your new game:", "Create");
    int result = dialog.exec();
    if (result != QDialog::Accepted) {
        throw std::runtime_error("Game name selection cancelled");
    }
    return dialog.getGameName();
}

MapType CreateGameButton::selectMap(QWidget* parent) {
    MapSelectionDialog dialog(parent);
    int result = dialog.exec();
    if (result != QDialog::Accepted) {
        throw std::runtime_error("Map selection cancelled");
    }
    return static_cast<MapType>(dialog.getSelectedMap());
}

std::pair<uint8_t, uint8_t> CreateGameButton::selectConfig(QWidget* parent) {
    CreateGameDialog dialog(parent);
    int result = dialog.exec();
    if (result != QDialog::Accepted) {
        throw std::runtime_error("Game configuration cancelled");
    }

    uint8_t players = dialog.getGameConfig().playerCount;
    uint8_t rounds = dialog.getGameConfig().rounds;
    return {players, rounds};
}

uint8_t CreateGameButton::selectTeam(QWidget* parent) {
    TeamSelectionDialog dialog(parent);
    int result = dialog.exec();
    if (result != QDialog::Accepted) {
        throw std::runtime_error("Team selection cancelled");
    }

    QString team = dialog.getSelectedTeam();
    if (team == "CT") {
        return Team::COUNTER_TERRORISTS;
    } else {
        return Team::TERRORISTS;
    }
}

uint8_t CreateGameButton::selectSkin(uint8_t teamId, QWidget* parent) {
    SkinSelectionDialog dialog(teamId, parent);
    int result = dialog.exec();
    if (result != QDialog::Accepted) {
        throw std::runtime_error("Skin selection cancelled");
    }
    return dialog.getSelectedSkin();
}

void CreateGameButton::showWaitingRoom(const QString& name, const QString& team, uint8_t skinId, QWidget* parent) {
    SkinMapper mapper;
    QString skinText = mapper.toString(mapper.toSkin(skinId));
    WaitingRoomDialog waitingRoom(name, team, skinText, protocol, parent);
    waitingRoom.exec();
}
