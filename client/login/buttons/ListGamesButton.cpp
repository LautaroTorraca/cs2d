#include "ListGamesButton.h"
#include "../MessageBox.h"
#include "login/dialogs/GameListDialog.h"
#include "login/mocks/GameListerMock.h"

ListGamesButton::ListGamesButton(QWidget* parent)
        : GameMenuButton("☰ List Games", parent) {
    connect(this, &QPushButton::clicked, this, &ListGamesButton::handleClick);
}

void ListGamesButton::handleClick() {
    QWidget* parentWindow = this->parentWidget();

    if (!parentWindow) {
        MessageBox msg(this);
        msg.showMessage("Internal Error",
                        "Unable to determine parent window to display the list.",
                        MessageType::Error);
        return;
    }

    try {
        GameListerMock lister;
        QStringList games = lister.listGameNames();

        GameListDialog dialog(games, parentWindow);
        if (dialog.exec() == QDialog::Accepted) {
            QString selected = dialog.getSelectedGame();
            MessageBox msg(this);
            msg.showMessage("Game Selected", QString("You selected <b>%1</b>.").arg(selected), MessageType::Success);
        }

    } catch (const std::exception& e) {
        MessageBox msg(this);
        msg.showMessage("Failed to List Games",
                        QString("An error occurred while listing games:\n\n%1").arg(e.what()),
                        MessageType::Error);
    }
}
