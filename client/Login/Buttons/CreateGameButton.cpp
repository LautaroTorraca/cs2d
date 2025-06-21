#include "CreateGameButton.h"
#include "client/Login/Flows/CreateGameFlow.h"

CreateGameButton::CreateGameButton(QWidget* parent, QLineEdit* usernameInput, Protocol& protocol)
        : GameMenuButton("➕  Create Game", parent), usernameInput(usernameInput), protocol(protocol) {
    connect(this, &QPushButton::clicked, this, &CreateGameButton::handleClick);
}

void CreateGameButton::handleClick() {
    CreateGameFlow flow(usernameInput, protocol, this->parentWidget());
    flow.run();
}
