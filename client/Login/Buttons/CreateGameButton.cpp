#include "CreateGameButton.h"

#include "Login/Flows/CreateGameFlow.h"
#include "Login/ServerMenu.h"
#include "Login/Audio/MusicManager.h"


CreateGameButton::CreateGameButton(QWidget* parent, QLineEdit* usernameInput, Protocol& protocol)
        : GameMenuButton("➕  Create Game", parent), usernameInput(usernameInput), protocol(protocol) {
    connect(this, &QPushButton::clicked, this, &CreateGameButton::handleClick);
}

void CreateGameButton::handleClick() {
    ServerMenu* menu = qobject_cast<ServerMenu*>(this->window());
    CreateGameFlow flow(usernameInput, protocol, this->parentWidget(), menu);
    flow.run();
}
