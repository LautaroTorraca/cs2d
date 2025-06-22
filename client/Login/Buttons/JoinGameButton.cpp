#include "JoinGameButton.h"
#include "Login/Flows/JoinGameFlow.h"

JoinGameButton::JoinGameButton(QWidget* parent, QLineEdit* usernameInput, Protocol& protocol)
        : GameMenuButton("▶ Join Game", parent),
        usernameInput(usernameInput),
        protocol(protocol) {
    connect(this, &QPushButton::clicked, this, &JoinGameButton::handleClick);
}

void JoinGameButton::handleClick() {
    ServerMenu* menu = qobject_cast<ServerMenu*>(this->window());
    JoinGameFlow flow(usernameInput, protocol, this->parentWidget(), menu);
    flow.run();
}
