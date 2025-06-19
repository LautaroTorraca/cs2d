#ifndef JOINGAMEBUTTON_H
#define JOINGAMEBUTTON_H

#include <QLineEdit>
#include "GameMenuButton.h"
#include "client/Protocol.h"

class JoinGameButton : public GameMenuButton {
    Q_OBJECT

private slots:
    void handleClick();

private:
    QLineEdit* usernameInput;
    Protocol& protocol;

    QString selectUsername();
    QString selectGameName(QWidget* parent);
    void validateGameExists(const QString& gameName);
    uint8_t selectTeam(QWidget* parent);
    uint8_t selectSkin(uint8_t teamId, QWidget* parent);
    void showWaitingRoom(const QString& username, const QString& team, uint8_t skinId, QWidget* parent);

public:
    JoinGameButton(QWidget* parent, QLineEdit* usernameInput, Protocol& protocol);
};

#endif // JOINGAMEBUTTON_H
