#include "ServerMenu.h"

#include "buttons/CreateGameButton.h"
#include "buttons/JoinGameButton.h"
#include "buttons/ListGamesButton.h"
#include "buttons/ExitGameButton.h"

#include <QVBoxLayout>
#include <QLineEdit>
#include <QPalette>
#include <QPixmap>
#include <QBrush>
#include <QCoreApplication>
#include <QWidget>

ServerMenu::ServerMenu(QWidget *parent) : QWidget(parent) {
    setupUI();
}

void ServerMenu::setupUI() {
    setWindowTitle("CS2D - Server Menu");
    resize(800, 600);

    // Load background TODO arreglar porque siempre entra en el fallbackPath
    QPalette palette;
    QPixmap backgroundPixmap(":/login/assets/image_background.png");

    if (backgroundPixmap.isNull()) {
        QString appDir = QCoreApplication::applicationDirPath();
        QStringList fallbackPaths = {
                appDir + "/../client/login/assets/image_background.png",
                "client/login/assets/image_background.png",
                "login/assets/image_background.png"
        };

        for (const auto& path : fallbackPaths) {
            backgroundPixmap = QPixmap(path);
            if (!backgroundPixmap.isNull()) break;
        }
    }

    if (!backgroundPixmap.isNull()) {
        backgroundPixmap = backgroundPixmap.scaled(size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
        palette.setBrush(QPalette::Window, QBrush(backgroundPixmap));
        setPalette(palette);
        setAutoFillBackground(true);
    } else {
        palette.setColor(QPalette::Window, QColor(20, 25, 35));
        setPalette(palette);
        setAutoFillBackground(true);
    }

    // Overlay for UI
    overlayWidget = std::make_unique<QWidget>(this);
    overlayWidget->setGeometry(0, 0, width(), height());
    overlayWidget->setAttribute(Qt::WA_TranslucentBackground);

    // Layout
    buttonLayout = std::make_unique<QVBoxLayout>(overlayWidget.get());
    buttonLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    buttonLayout->setSpacing(20);
    buttonLayout->setContentsMargins(60, 150, 0, 0);

    // Username input
    usernameInput = std::make_unique<QLineEdit>();
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
    buttonLayout->addWidget(usernameInput.get());

    // Buttons
    buttonLayout->addWidget(new CreateGameButton(this, usernameInput.get()));
    buttonLayout->addWidget(new JoinGameButton(this, usernameInput.get()));
    buttonLayout->addWidget(new ListGamesButton(this));
    buttonLayout->addWidget(new ExitGameButton(this));
}

void ServerMenu::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    if (overlayWidget) {
        overlayWidget->setGeometry(0, 0, width(), height());
    }

    QPalette palette;
    QPixmap backgroundPixmap(":/login/assets/image_background.png");
    if (!backgroundPixmap.isNull()) {
        backgroundPixmap = backgroundPixmap.scaled(size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
        palette.setBrush(QPalette::Window, QBrush(backgroundPixmap));
        setPalette(palette);
    }
}
