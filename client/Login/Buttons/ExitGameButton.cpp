#include "ExitGameButton.h"
#include "../dialogs/ConfirmExitDialog.h"

ExitGameButton::ExitGameButton(QWidget* parent)
        : GameMenuButton("✖ Exit", parent) {
    connect(this, &QPushButton::clicked, this, &ExitGameButton::handleClick);
}

void ExitGameButton::handleClick() {
    ConfirmExitDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted && dialog.userConfirmed()) {
        QWidget* top = this->window();
        if (top) top->close();
    }
}
