#include "GameListDialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMessageBox>

GameListDialog::GameListDialog(const QStringList& games, QWidget* parent)
        : QDialog(parent), selectedGame("") {
    setWindowTitle("🎮 Select Game to Join");
    resize(400, 300);
    setModal(true);
    applyStyle();
    setupUI(games);
}

void GameListDialog::applyStyle() {
    setStyleSheet(R"(
        QWidget {
            background-color: #1f1f1f;
            color: #ffffff;
            font-family: 'Segoe UI', sans-serif;
        }

        QLabel {
            font-size: 18px;
            font-weight: bold;
            padding: 10px;
        }

        QListWidget {
            background-color: #2a2a2a;
            border: none;
            font-size: 15px;
            padding: 5px;
        }

        QListWidget::item {
            padding: 10px;
            margin: 4px;
            border-radius: 6px;
        }

        QListWidget::item:selected {
            background-color: #3d7ff5;
            color: white;
        }

        QPushButton {
            padding: 8px 18px;
            font-weight: bold;
            border-radius: 6px;
            background-color: #3d3d3d;
            color: white;
            border: 1px solid #666;
        }

        QPushButton:hover {
            background-color: #505050;
        }

        QPushButton:pressed {
            background-color: #3a3a3a;
        }
    )");
}

void GameListDialog::setupUI(const QStringList& games) {
    auto* mainLayout = new QVBoxLayout(this);

    auto* title = new QLabel("Choose a game to join:");
    mainLayout->addWidget(title, 0, Qt::AlignHCenter);

    listWidget = new QListWidget(this);
    listWidget->addItems(games);
    mainLayout->addWidget(listWidget);

    auto* buttonLayout = new QHBoxLayout();

    joinButton = new QPushButton("Join");
    auto* cancelButton = new QPushButton("Cancel");

    buttonLayout->addStretch();
    buttonLayout->addWidget(joinButton);
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addStretch();

    mainLayout->addLayout(buttonLayout);

    connect(joinButton, &QPushButton::clicked, this, &GameListDialog::handleJoin);
    connect(cancelButton, &QPushButton::clicked, this, &GameListDialog::reject);
}

void GameListDialog::handleJoin() {
    QListWidgetItem* item = listWidget->currentItem();
    if (!item) {
        QMessageBox::warning(this, "No Selection", "Please select a game to join.");
        return;
    }

    selectedGame = item->text();
    accept();
}

QString GameListDialog::getSelectedGame() const {
    return selectedGame;
}
