#pragma once

#include <QLineEdit>

#include "client/Protocol.h"

#include "GameMenuButton.h"

class ListGamesButton : public GameMenuButton {
    Q_OBJECT

public:
    explicit ListGamesButton(QWidget* parent, QLineEdit* usernameInput ,Protocol& protocol);
    uint8_t selectTeam(QWidget* parent);
    uint8_t selectSkin(uint8_t teamId, QWidget* parent);
    QString selectUsername();
    void showWaitingRoom(const QString& username, const QString& team, uint8_t skinId, QWidget* parent);

private slots:
    void handleClick();

private:
    QLineEdit* usernameInput;
    Protocol& protocol;

};
