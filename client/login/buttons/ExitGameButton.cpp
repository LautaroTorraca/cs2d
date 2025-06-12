#include "ExitGameButton.h"
#include <QMessageBox>

ExitGameButton::ExitGameButton(QWidget* parent)
        : GameMenuButton("✖ Exit", parent) {
    connect(this, &QPushButton::clicked, this, &ExitGameButton::handleClick);
}

void ExitGameButton::handleClick() {
    QMessageBox::StandardButton reply = QMessageBox::question(
            this,
            "Exit Game",
            "Are you sure you want to exit?",
            QMessageBox::Yes | QMessageBox::No
    );

    if (reply == QMessageBox::Yes) {
        QWidget* top = this->window();
        if (top) top->close();
    }
}
