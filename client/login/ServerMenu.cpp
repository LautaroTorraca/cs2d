#include "ServerMenu.h"
#include "GameCreatorMock.h"
#include "GameListerMock.h"
#include "CreateGameDialog.h"
#include "TeamSelectionDialog.h"
#include "SkinSelectionDialog.h"
#include "WaitingRoomDialog.h"
#include "GameDTO.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QPixmap>

ServerMenu::ServerMenu(QWidget *parent) : QWidget(parent) {
    setupUI();
}

void ServerMenu::setupUI() {
    setWindowTitle("CS2D - Server Menu");
    resize(800, 600);

    QPixmap bg("cs2d_menu.png");
    backgroundLabel = std::make_unique<QLabel>(this);
    if (bg.isNull()) {
        backgroundLabel->setText("Background image not found");
    } else {
        backgroundLabel->setPixmap(bg.scaled(size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
    }
    backgroundLabel->setScaledContents(true);
    backgroundLabel->setGeometry(0, 0, width(), height());

    overlayWidget = std::make_unique<QWidget>(this);
    overlayWidget->setGeometry(0, 0, width(), height());
    overlayWidget->setAttribute(Qt::WA_TranslucentBackground);

    buttonLayout = std::make_unique<QVBoxLayout>(overlayWidget.get());
    buttonLayout->setAlignment(Qt::AlignCenter);
    buttonLayout->setSpacing(15);
    buttonLayout->setContentsMargins(300, 150, 300, 100);

    usernameInput = std::make_unique<QLineEdit>();
    usernameInput->setPlaceholderText("Enter your name");
    buttonLayout->addWidget(usernameInput.get());

    createGameBtn = std::make_unique<QPushButton>("Create Game");
    joinGameBtn = std::make_unique<QPushButton>("Join Game");
    listGamesBtn = std::make_unique<QPushButton>("List Games");
    exitBtn = std::make_unique<QPushButton>("Exit");

    QList<QPushButton *> buttons = {
        createGameBtn.get(), joinGameBtn.get(), listGamesBtn.get(), exitBtn.get()
    };

    for (QPushButton *btn : buttons) {
        btn->setStyleSheet(
            "QPushButton { background-color: rgba(0,0,0,0.6); color: white; font-size: 18px; padding: 10px; border-radius: 10px; }"
            "QPushButton:hover { background-color: rgba(255,255,255,0.2); }"
        );
        buttonLayout->addWidget(btn);
    }

    connect(createGameBtn.get(), &QPushButton::clicked, this, &ServerMenu::handleCreateGame);
    connect(joinGameBtn.get(), &QPushButton::clicked, this, &ServerMenu::handleJoinGame);
    connect(listGamesBtn.get(), &QPushButton::clicked, this, &ServerMenu::handleListGames);
    connect(exitBtn.get(), &QPushButton::clicked, this, &ServerMenu::handleExitGame);
}

void ServerMenu::handleCreateGame() {
    QString name = usernameInput->text();
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter your name.");
        return;
    }

    //TODO Llamar al gameCreator real no mock
    GameCreatorMock gameCreator;
    GameDTO dto = gameCreator.openCreateGameDialog(this);  //aca

    // Hace team selection -> skin -> waiting room
    TeamSelectionDialog teamDialog(this);
    if (teamDialog.exec() != QDialog::Accepted) return;

    QString selectedTeam = teamDialog.getSelectedTeam();

    SkinSelectionDialog skinDialog(selectedTeam, this);
    if (skinDialog.exec() != QDialog::Accepted) return;

    QString selectedSkin = skinDialog.getSelectedSkin();

    WaitingRoomDialog waitingRoom(dto, name, selectedTeam, selectedSkin, this);
    waitingRoom.exec();
}

void ServerMenu::handleJoinGame() {
    QString name = usernameInput->text();
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter your name.");
        return;
    }

    QMessageBox::information(this, "Join Game", "");
}

void ServerMenu::handleListGames() {
    //TODO reemplazar con el que sabe la lista de jugadores
    GameListerMock lister;
    lister.showAvailableGames(this);
}

void ServerMenu::handleExitGame() {
    close();
}
