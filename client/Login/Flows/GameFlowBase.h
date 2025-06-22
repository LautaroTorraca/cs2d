#pragma once
#include <QString>
#include <QWidget>
#include <QLineEdit>
#include "client/Protocol.h"
using namespace Client;

#pragma once
#include <QString>
#include <QWidget>
#include <QLineEdit>
#include "client/Protocol.h"
#include "Login/ServerMenu.h"
using namespace Client;

class GameFlowBase {
protected:
    QLineEdit* usernameInput;
    Protocol& protocol;
    QWidget* parent;
    ServerMenu* menu;

    GameFlowBase(QLineEdit* usernameInput, Protocol& protocol, QWidget* parent, ServerMenu* menu = nullptr);

    QString getUsername();
    PlayerChoicesDTO getPlayerChoices();
    void showWaitingRoom(const QString& username, Team team, Skin skin);


private:
    Team askTeam();
    Skin askSkin(Team team);
};