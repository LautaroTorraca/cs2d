#include "JoinGameButton.h"
#include "client/Login/Flows/JoinGameFlow.h"

JoinGameButton::JoinGameButton(QWidget* parent, QLineEdit* usernameInput, Protocol& protocol)
        : GameMenuButton("▶ Join Game", parent),
        usernameInput(usernameInput),
        protocol(protocol) {
    connect(this, &QPushButton::clicked, this, &JoinGameButton::handleClick);
}

void JoinGameButton::handleClick() {
    JoinGameFlow flow(usernameInput, protocol, this->parentWidget());
    flow.run();
}
