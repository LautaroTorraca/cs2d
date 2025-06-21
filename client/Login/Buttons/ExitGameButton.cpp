#include "ExitGameButton.h"
#include "../Dialogs/ConfirmExitDialog.h"


ExitGameButton::ExitGameButton(QWidget* parent)
        : GameMenuButton("✖ Exit", parent) {
    connect(this, &QPushButton::clicked, this, &ExitGameButton::handleClick);
}


void ExitGameButton::handleClick() {
    QWidget* parent = this->parentWidget();

    ConfirmExitDialog confirmDialog(parent);
    int result = confirmDialog.exec();

    if (result == QDialog::Accepted && confirmDialog.userConfirmed()) {
        QWidget* window = this->window();
        if (window) {
            window->close();
        }
    }
}
