#include "ListGamesButton.h"
#include "Login/Flows/ListGameFlow.h"

ListGamesButton::ListGamesButton(QWidget* parent, QLineEdit* usernameInput, Protocol& protocol)
        : GameMenuButton("☰ List Games", parent),
        usernameInput(usernameInput),
        protocol(protocol) {
    connect(this, &QPushButton::clicked, this, &ListGamesButton::handleClick);
}

void ListGamesButton::handleClick() {
    ListGameFlow flow(usernameInput, protocol, this->parentWidget());
    flow.run();
}
