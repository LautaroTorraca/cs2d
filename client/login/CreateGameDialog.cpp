#include "CreateGameDialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>


//fiz memory leak
CreateGameDialog::CreateGameDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Game Setup");
    setModal(true);
    resize(300, 200);

    auto *layout = new QVBoxLayout(this);

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

    confirmButton = new QPushButton("Confirm");

    layout->addWidget(playerLabel);
    layout->addWidget(playerSpinBox);
    layout->addWidget(roundsLabel);
    layout->addWidget(roundsSpinBox);
    layout->addWidget(confirmButton);

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
