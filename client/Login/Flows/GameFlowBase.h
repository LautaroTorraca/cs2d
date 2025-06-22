#pragma once
#include <QString>
#include <QWidget>
#include <QLineEdit>
#include "client/Protocol.h"
using namespace Client;

class GameFlowBase {
protected:
    QLineEdit* usernameInput;
    Protocol& protocol;
    QWidget* parent;

    GameFlowBase(QLineEdit* usernameInput, Protocol& protocol, QWidget* parent);

    QString getUsername();
    PlayerChoicesDTO getPlayerChoices();
    void showWaitingRoom(const QString& username, Team team, Skin skin);

private:
    Team askTeam();
    Skin askSkin(Team team);
};

