#include "TeamSelectionDialog.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

TeamSelectionDialog::TeamSelectionDialog(QWidget *parent)
    : QDialog(parent), selectedTeam("") {
    setWindowTitle("Choose Your Team");
    setModal(true);
    resize(300, 150);

    auto *layout = new QVBoxLayout(this);

    auto *label = new QLabel("Select a team:");
    layout->addWidget(label);

    auto *ctButton = new QPushButton("Counter-Terrorist (CT)");
    auto *ttButton = new QPushButton("Terrorist (TT)");

    layout->addWidget(ctButton);
    layout->addWidget(ttButton);

    connect(ctButton, &QPushButton::clicked, this, &TeamSelectionDialog::selectCT);
    connect(ttButton, &QPushButton::clicked, this, &TeamSelectionDialog::selectTT);
}

void TeamSelectionDialog::selectCT() {
    selectedTeam = "CT";
    accept();
}

void TeamSelectionDialog::selectTT() {
    selectedTeam = "TT";
    accept();
}

QString TeamSelectionDialog::getSelectedTeam() const {
    return selectedTeam;
}
