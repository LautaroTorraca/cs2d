#include "ListGamesButton.h"

#include <QStringList>
#include <vector>

#include "../MessageBox.h"
#include "../dialogs/GameListDialog.h"
#include "login/SkinTraslator.h"
#include "login/dialogs/SkinSelectionDialog.h"
#include "login/dialogs/TeamSelectionDialog.h"
#include "login/dialogs/WaitingRoomDialog.h"

ListGamesButton::ListGamesButton(QWidget* parent, QLineEdit* usernameInput  ,Protocol& protocol)
        : GameMenuButton("☰ List Games", parent), usernameInput(usernameInput) ,protocol(protocol) {
    connect(this, &QPushButton::clicked, this, &ListGamesButton::handleClick);
}

void ListGamesButton::handleClick() {
    QWidget* parentWindow = this->parentWidget();
    QString name = selectUsername();
    if (name.isEmpty()) return;

    if (!parentWindow) {
        MessageBox msg(this);
        msg.showMessage("Internal Error",
                        "Unable to determine parent window to display the list.",
                        MessageType::Error);
        return;
    }

    try {
        GamesList gameList = protocol.getGamesList();
        const std::vector<std::string>& gameNames = gameList.games;

        if (gameNames.empty()) {
            MessageBox msg(this);
            msg.showMessage("No Games Found",
                            "There are no active games right now.",
                            MessageType::Info);
            return;
        }

        QStringList formattedGames;
        for (const std::string& game : gameNames) {
            formattedGames << QString::fromStdString(game);
        }

        GameListDialog dialog(formattedGames, parentWindow);
        if (dialog.exec() == QDialog::Accepted) {
            QString selected = dialog.getSelectedGame();
            MessageBox msg(this);
            msg.showMessage("Game Selected",
                            QString("You selected <b>%1</b>.").arg(selected),
                            MessageType::Success);

            uint8_t teamId = selectTeam(parentWindow);
            uint8_t skinId = selectSkin(teamId, parentWindow);


            protocol.joinLobby(selected.toStdString());

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

            showWaitingRoom(name, teamName, skinId, parentWindow);


        }

    } catch (const std::exception& e) {
        MessageBox msg(this);
        msg.showMessage("Failed to List Games",
                        QString("An error occurred while listing games:\n\n%1").arg(e.what()),
                        MessageType::Error);
    }
}


uint8_t ListGamesButton::selectTeam(QWidget* parent) {
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

uint8_t ListGamesButton::selectSkin(uint8_t teamId, QWidget* parent) {
    SkinSelectionDialog dialog(teamId, parent);
    int result = dialog.exec();
    if (result != QDialog::Accepted) {
        throw std::runtime_error("Skin selection cancelled");
    }
    return dialog.getSelectedSkin();
}

void ListGamesButton::showWaitingRoom(const QString& name, const QString& team, uint8_t skinId, QWidget* parent) {
    SkinMapper mapper;
    QString skinText = mapper.toString(mapper.toSkin(skinId));
    WaitingRoomDialog waitingRoom(name, team, skinText, protocol, parent);
    waitingRoom.exec();
}

QString ListGamesButton::selectUsername() {
    QString name = usernameInput->text().trimmed();
    if (name.isEmpty()) {
        MessageBox msg(this);
        msg.showMessage("Name Required", "Please enter your name to continue.", MessageType::Warning);
    }
    return name;
}
