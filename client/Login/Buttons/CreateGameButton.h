#pragma once
#include <QLineEdit>
#include "GameMenuButton.h"
#include "client/Protocol.h"

class CreateGameButton : public GameMenuButton {
    Q_OBJECT

private:
    QLineEdit* usernameInput;
    Protocol& protocol;

private slots:
    void handleClick();

public:
    CreateGameButton(QWidget* parent, QLineEdit* usernameInput, Protocol& protocol);
};

