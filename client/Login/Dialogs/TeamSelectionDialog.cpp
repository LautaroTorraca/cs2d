#include "TeamSelectionDialog.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

#include "server/Team.h"

TeamSelectionDialog::TeamSelectionDialog(QWidget* parent)
        : QDialog(parent), selectedTeam("") {
    setWindowTitle("Choose Your Team");
    setModal(true);
    resize(380, 240);
    setupUI();
}

void TeamSelectionDialog::setupUI() {
    setStyleSheet(R"(
        QWidget {
            background-color: #121212;
            color: #f5f5f5;
            font-family: 'Segoe UI', sans-serif;
            font-size: 16px;
        }

        QLabel {
            font-size: 20px;
            font-weight: bold;
            margin-top: 20px;
            margin-bottom: 25px;
        }

        QPushButton {
            background-color: #1e1e1e;
            color: white;
            border: 2px solid #444;
            border-radius: 12px;
            padding: 14px;
            font-size: 17px;
            font-weight: 600;
            margin: 10px 20px;
        }

        QPushButton:hover {
            background-color: #2c2c2c;
            border-color: #666;
        }

        QPushButton:pressed {
            background-color: #3a3a3a;
        }
    )");

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);

    QLabel* label = new QLabel("Select your team:");
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);

    QPushButton* ctButton = new QPushButton("🛡 Counter-Terrorists");
    QPushButton* ttButton = new QPushButton("💣 Terrorists");

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

Team TeamSelectionDialog::getSelectedTeam() const {
    if (selectedTeam == "CT") return Team::COUNTER_TERRORISTS;
    return Team::TERRORISTS;
}
