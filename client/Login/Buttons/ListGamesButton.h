#pragma once

#include <QLineEdit>
#include "client/Protocol.h"
#include "GameMenuButton.h"
using namespace Client;

class ListGamesButton : public GameMenuButton {
    Q_OBJECT

public:
    explicit ListGamesButton(QWidget* parent, QLineEdit* usernameInput, Protocol& protocol);

private slots:
    void handleClick();

private:
    QLineEdit* usernameInput;
    Protocol& protocol;
};
