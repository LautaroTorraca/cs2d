#include "JoinGameButton.h"
#include "../MessageBox.h"
#include "login/mocks/GameListerMock.h"
#include "login/dialogs/GameNameDialog.h"

JoinGameButton::JoinGameButton(QWidget* parent, QLineEdit* usernameInput)
        : GameMenuButton("▶ Join Game", parent), usernameInput(usernameInput) {
    connect(this, &QPushButton::clicked, this, &JoinGameButton::handleClick);
}

void JoinGameButton::handleClick() {
    QString name = usernameInput->text().trimmed();
    if (name.isEmpty()) {
        MessageBox msg(this);
        msg.showMessage("Name Required", "Please enter your name to join a game.", MessageType::Warning);
        usernameInput->setFocus();
        return;
    }

    GameNameDialog dialog(this);
    int result = dialog.exec();
    if (result != QDialog::Accepted) {
        return;
    }

    QString gameName = dialog.getGameName();
    if (gameName.isEmpty()) {
        MessageBox msg(this);
        msg.showMessage("Game Name Required", "You must enter a valid game name to join.", MessageType::Warning);
        return;
    }

    GameListerMock lister;
    QStringList availableGames = lister.listGameNames();

    bool gameFound = false;
    for (const QString& g : availableGames) {
        if (QString::compare(g, gameName, Qt::CaseInsensitive) == 0) {
            gameFound = true;
            break;
        }
    }

    if (!gameFound) {
        MessageBox msg(this);
        msg.showMessage("Game Not Found", QString("No active game found with the name '<b>%1</b>'.").arg(gameName), MessageType::Error);
        return;
    }

    MessageBox msg(this);
    msg.showMessage("Game Joined", QString("You're joining <b>%1</b> as <b>%2</b>.").arg(gameName, name), MessageType::Success);
}
