#include "ServerMenu.h"

#include "Widgets/UsernameInput.h"
#include "Buttons/CreateGameButton.h"
#include "Buttons/JoinGameButton.h"
#include "Buttons/ListGamesButton.h"
#include "Buttons/ExitGameButton.h"
#include "Visual/MenuBackground.h"
#include "Audio/MusicManager.h"

ServerMenu::ServerMenu(const char* port, QWidget* parent)
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
    setupBackgroundMusic();
}

void ServerMenu::setupBackground() {
    MenuBackground::applyTo(this);
}

void ServerMenu::setupInput() {
    usernameInput = new UsernameInput(this);
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

void ServerMenu::setupBackgroundMusic() {
    musicManager = new MusicManager(this);
    musicManager->loadBackgroundMusic("menu_music.mp3", 0.3f);
}

void ServerMenu::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    if (overlayWidget) {
        overlayWidget->setGeometry(0, 0, width(), height());
    }
    setupBackground();
}