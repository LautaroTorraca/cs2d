#include "CreateGameDialog.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QMessageBox>

CreateGameDialog::CreateGameDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle("Create Game");
    setModal(true);
    resize(480, 300);
    setupUI();
}

void CreateGameDialog::setupUI() {
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

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(30, 30, 30, 30);

    QLabel* playerLabel = new QLabel("Number of Players:");
    playerSpinBox = new QSpinBox();
    playerSpinBox->setMinimum(2);
    playerSpinBox->setMaximum(10);
    playerSpinBox->setValue(4);

    QLabel* roundsLabel = new QLabel("Number of Rounds:");
    roundsSpinBox = new QSpinBox();
    roundsSpinBox->setMinimum(0);
    roundsSpinBox->setMaximum(50);
    roundsSpinBox->setSingleStep(1);
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

bool CreateGameDialog::isValidRound(int rounds) const {
    return rounds % 2 == 0;
}

void CreateGameDialog::handleConfirm() {
    int rounds = roundsSpinBox->value();

    if (!isValidRound(rounds)) {
        QMessageBox::warning(this, "Invalid Input", "Please enter an even number between 0 and 50.");
        return;
    }

    config.playerCount = static_cast<uint8_t>(playerSpinBox->value());
    config.rounds = static_cast<uint8_t>(rounds);

    accept();
}

GameDTO CreateGameDialog::getGameConfig() const {
    return config;
}
