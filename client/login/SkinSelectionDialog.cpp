#include "SkinSelectionDialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>

SkinSelectionDialog::SkinSelectionDialog(const QString &team, QWidget *parent)
    : QDialog(parent), selectedSkin("") {
    setWindowTitle("Select Skin");
    setModal(true);
    resize(300, 150);

    auto *layout = new QVBoxLayout(this);

    auto *label = new QLabel("Choose your skin:");
    layout->addWidget(label);

    skinComboBox = new QComboBox(this);
    loadSkinsForTeam(team);
    layout->addWidget(skinComboBox);

    confirmButton = new QPushButton("Confirm");
    layout->addWidget(confirmButton);

    connect(confirmButton, &QPushButton::clicked, this, &SkinSelectionDialog::handleConfirm);
}

void SkinSelectionDialog::loadSkinsForTeam(const QString &team) {
    if (team == "CT") {
        skinComboBox->addItems({"CT - Urban", "CT - FBI", "CT - GIGN"});
    } else if (team == "TT") {
        skinComboBox->addItems({"TT - Phoenix", "TT - Elite", "TT - Guerrilla"});
    }
}

void SkinSelectionDialog::handleConfirm() {
    selectedSkin = skinComboBox->currentText();
    accept();
}

QString SkinSelectionDialog::getSelectedSkin() const {
    return selectedSkin;
}
