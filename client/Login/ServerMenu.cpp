#include "ServerMenu.h"

#include "Buttons/CreateGameButton.h"
#include "Buttons/JoinGameButton.h"
#include "Buttons/ListGamesButton.h"
#include "Buttons/ExitGameButton.h"
#include "Visual/MenuBackground.h"

#include <QCoreApplication>

ServerMenu::ServerMenu(const char* port, QWidget *parent)
        : protocol("localhost", port), QWidget(parent) {
    setupUI();
}

void ServerMenu::setupUI() {
    setWindowTitle("CS2D - Server Menu");
    resize(800, 600);

    setupBackground();

    overlayWidget = new QWidget(this);
    overlayWidget->setGeometry(0, 0, width(), height());
    overlayWidget->setAttribute(Qt::WA_TranslucentBackground);

    buttonLayout = new QVBoxLayout(overlayWidget);
    buttonLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    buttonLayout->setSpacing(20);
    buttonLayout->setContentsMargins(60, 150, 0, 0);

    setupInput();
    setupButtons();
}

void ServerMenu::setupBackground() {
    MenuBackground::applyTo(this);
}

void ServerMenu::setupInput() {
    usernameInput = new QLineEdit(this);
    usernameInput->setPlaceholderText("Enter your name");
    usernameInput->setFixedWidth(220);
    usernameInput->setStyleSheet(R"(
        QLineEdit {
            background-color: rgba(255, 255, 255, 0.1);
            color: white;
            font-size: 16px;
            font-weight: bold;
            padding: 12px;
            border: 2px solid rgba(255, 255, 255, 0.2);
            border-radius: 8px;
        }
        QLineEdit:focus {
            border: 2px solid rgba(100, 150, 255, 0.8);
            background-color: rgba(255, 255, 255, 0.15);
        }
        QLineEdit::placeholder {
            color: rgba(255, 255, 255, 0.6);
        }
    )");
    buttonLayout->addWidget(usernameInput);
}

void ServerMenu::setupButtons() {
    createGameButton = new CreateGameButton(this, usernameInput, protocol);
    joinGameButton = new JoinGameButton(this, usernameInput, protocol);
    listGamesButton = new ListGamesButton(this, usernameInput, protocol);
    exitGameButton = new ExitGameButton(this);

    buttonLayout->addWidget(createGameButton);
    buttonLayout->addWidget(joinGameButton);
    buttonLayout->addWidget(listGamesButton);
    buttonLayout->addWidget(exitGameButton);
}

void ServerMenu::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    if (overlayWidget) {
        overlayWidget->setGeometry(0, 0, width(), height());
    }
    setupBackground();
}
