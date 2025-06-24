#include "GameFlowBase.h"

#include "GameFlowUtils.h"
#include "../Mappers/SkinTraslator.h"
#include "client/Login/Mappers/TeamMapper.h"
#include "client/Login/Dialogs/TeamSelectionDialog.h"
#include "client/Login/Dialogs/SkinSelectionDialog.h"
#include "client/Login/Dialogs/WaitingRoomDialog.h"

GameFlowBase::GameFlowBase(QLineEdit* usernameInput, Protocol& protocol, QWidget* parent, ServerMenu* menu)
        : usernameInput(usernameInput), protocol(protocol), parent(parent), menu(menu) {}

QString GameFlowBase::getUsername() {
    return GameFlowUtils::getUsername(usernameInput, parent);
}

PlayerChoicesDTO GameFlowBase::getPlayerChoices() {
    Team team = askTeam();
    Skin skin = askSkin(team);
    QString username = getUsername();
    return PlayerChoicesDTO(username.toStdString(), team, skin);
}

void GameFlowBase::showWaitingRoom(const QString& username, Team team, Skin skin) {
    SkinMapper skinMapper;
    TeamMapper teamMapper;
    QString teamStr = teamMapper.toString(team);
    QString skinStr = skinMapper.toString(skin);

    WaitingRoomDialog waitingRoom(username, teamStr, skinStr, protocol, menu, parent);

    waitingRoom.exec();

}

Team GameFlowBase::askTeam() {
    uint8_t teamId = GameFlowUtils::askTeam(parent, protocol);
    return static_cast<Team>(teamId);
}

Skin GameFlowBase::askSkin(Team team) {
    uint8_t skinId = GameFlowUtils::askSkin(static_cast<uint8_t>(team), parent, protocol);
    return static_cast<Skin>(skinId);
}