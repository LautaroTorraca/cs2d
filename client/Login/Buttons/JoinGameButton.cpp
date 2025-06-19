#include "JoinGameButton.h"

#include "../MessageBox.h"
#include "../SkinTraslator.h"
#include "client/LobbyDTO.h"
#include "login/dialogs/GameNameDialog.h"
#include "login/dialogs/SkinSelectionDialog.h"
#include "login/dialogs/TeamSelectionDialog.h"
#include "login/dialogs/WaitingRoomDialog.h"
#include "server/Team.h"

#include <iostream>
#include <stdexcept>

JoinGameButton::JoinGameButton(QWidget* parent, QLineEdit* usernameInput, Protocol& protocol)
        : GameMenuButton("▶ Join Game", parent),
        usernameInput(usernameInput),
        protocol(protocol) {
    connect(this, &QPushButton::clicked, this, &JoinGameButton::handleClick);
}

void JoinGameButton::handleClick() {
    QWidget* parent = this->parentWidget();
    QString name = selectUsername();
    if (name.isEmpty()) return;

    try {
        QString gameName = selectGameName(parent);
        validateGameExists(gameName);

        uint8_t teamId = selectTeam(parent);
        uint8_t skinId = selectSkin(teamId, parent);


        protocol.joinLobby(gameName.toStdString());

        LobbyConnectionDTO lobbyStatus = protocol.getLobbyConnection();
        if (lobbyStatus.status != ConnectionStatus::SUCCESS) {
            MessageBox msg(this);
            msg.showMessage("Failed to Join", "Unable to join the selected game lobby.", MessageType::Error);
            return;
        }

        PlayerChoicesDTO playerChoices(name.toStdString(),
                                       static_cast<Team>(teamId),
                                       static_cast<Skin>(skinId));

        QString teamName;
        if (teamId == Team::COUNTER_TERRORISTS) {
            teamName = "CT";
        } else {
            teamName = "TT";
        }

        showWaitingRoom(name, teamName, skinId, parent);

    } catch (const std::exception& e) {
        MessageBox msg(this);
        msg.showMessage("❌ Failed to Join Game",
                        QString("An unexpected error occurred:\n\n%1").arg(e.what()),
                        MessageType::Error);
    }
}

QString JoinGameButton::selectUsername() {
    QString name = usernameInput->text().trimmed();
    if (name.isEmpty()) {
        MessageBox msg(this);
        msg.showMessage("Name Required", "Please enter your name to continue.", MessageType::Warning);
    }
    return name;
}

QString JoinGameButton::selectGameName(QWidget* parent) {
    GameNameDialog dialog(parent, "Enter the name of the game you want to join:", "Join");
    int result = dialog.exec();
    if (result != QDialog::Accepted) {
        throw std::runtime_error("Game name selection cancelled");
    }
    return dialog.getGameName();
}


void JoinGameButton::validateGameExists(const QString& gameName) {
    GamesList gameList = protocol.getGamesList();
    std::vector<std::string> availableGames = gameList.games;

    for (const std::string& game : availableGames) {
        if (QString::fromStdString(game) == gameName) {
            return;
        }
    }

    throw std::runtime_error(QString("No active game found with the name '%1'.").arg(gameName).toStdString());
}

uint8_t JoinGameButton::selectTeam(QWidget* parent) {
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

uint8_t JoinGameButton::selectSkin(uint8_t teamId, QWidget* parent) {
    SkinSelectionDialog dialog(teamId, parent);
    int result = dialog.exec();
    if (result != QDialog::Accepted) {
        throw std::runtime_error("Skin selection cancelled");
    }
    return dialog.getSelectedSkin();
}

void JoinGameButton::showWaitingRoom(const QString& name, const QString& team, uint8_t skinId, QWidget* parent) {
    SkinMapper mapper;
    QString skinText = mapper.toString(mapper.toSkin(skinId));
    WaitingRoomDialog waitingRoom(name, team, skinText, protocol, parent);
    waitingRoom.exec();
}
