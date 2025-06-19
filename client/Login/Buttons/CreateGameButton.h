#ifndef CREATEGAMEBUTTON_H
#define CREATEGAMEBUTTON_H

#include <QLineEdit>
#include "GameMenuButton.h"
#include "client/Protocol.h"

class CreateGameButton : public GameMenuButton {
    Q_OBJECT

private slots:
    void handleClick();

private:
    QLineEdit* usernameInput;
    Protocol& protocol;

    QString selectUsername();
    QString selectGameName(QWidget* parent);
    MapType selectMap(QWidget* parent);
    std::pair<uint8_t, uint8_t> selectConfig(QWidget* parent);
    uint8_t selectTeam(QWidget* parent);
    uint8_t selectSkin(uint8_t teamId, QWidget* parent);
    void showWaitingRoom(const QString& username, const QString& team, uint8_t skinId, QWidget* parent);

public:
    CreateGameButton(QWidget* parent, QLineEdit* usernameInput, Protocol& protocol);
};

#endif // CREATEGAMEBUTTON_H
