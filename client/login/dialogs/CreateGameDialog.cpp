#include "CreateGameDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>

CreateGameDialog::CreateGameDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Create Game");
    setModal(true);
    resize(480, 300);

    setStyleSheet(R"(
        QWidget {
            background-color: #121212;
            color: #f0f0f0;
            font-family: 'Segoe UI', sans-serif;
            font-size: 16px;
        }

        QLabel {
            font-size: 18px;
            font-weight: 600;
            margin-top: 20px;
            margin-bottom: 8px;
        }

        QSpinBox {
            background-color: #1f1f1f;
            color: white;
            border: 2px solid #444;
            border-radius: 8px;
            padding: 6px;
            font-size: 16px;
        }

        QPushButton {
            background-color: #007acc;
            color: white;
            border: none;
            border-radius: 10px;
            font-size: 17px;
            font-weight: bold;
            padding: 10px 20px;
            margin-top: 30px;
        }

        QPushButton:hover {
            background-color: #0095ff;
        }

        QPushButton:pressed {
            background-color: #005f99;
        }
    )");

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(30, 30, 30, 30);

    auto *playerLabel = new QLabel("Number of Players:");
    playerSpinBox = new QSpinBox();
    playerSpinBox->setMinimum(2);
    playerSpinBox->setMaximum(10);
    playerSpinBox->setValue(4);

    auto *roundsLabel = new QLabel("Number of Rounds:");
    roundsSpinBox = new QSpinBox();
    roundsSpinBox->setMinimum(1);
    roundsSpinBox->setMaximum(50);
    roundsSpinBox->setValue(10);

    confirmButton = new QPushButton("Start Game");

    mainLayout->addWidget(playerLabel);
    mainLayout->addWidget(playerSpinBox);
    mainLayout->addWidget(roundsLabel);
    mainLayout->addWidget(roundsSpinBox);
    mainLayout->addStretch();
    mainLayout->addWidget(confirmButton, 0, Qt::AlignCenter);

    connect(confirmButton, &QPushButton::clicked, this, &CreateGameDialog::handleConfirm);
}

void CreateGameDialog::handleConfirm() {
    config.playerCount = playerSpinBox->value();
    config.rounds = roundsSpinBox->value();
    accept();
}

GameDTO CreateGameDialog::getGameConfig() const {
    return config;
}
