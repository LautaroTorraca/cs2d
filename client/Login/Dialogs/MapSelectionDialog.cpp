#include <QLabel>
#include "MapSelectionDialog.h"
#include "server/Constants/MapTypeConstants.h"
MapSelectionDialog::MapSelectionDialog(QWidget* parent)
        : QDialog(parent), selectedMap(static_cast<uint8_t>(MapType::DUST)) {
    setWindowTitle("Select Map");
    setModal(true);
    resize(480, 240);

    setStyleSheet(R"(
        QWidget {
            background-color: #121212;
            color: white;
            font-family: 'Segoe UI', sans-serif;
        }
        QPushButton {
            background-color: #1f1f1f;
            color: white;
            border: 2px solid #444;
            border-radius: 10px;
            padding: 12px;
            font-size: 16px;
            font-weight: bold;
            margin: 8px;
        }
        QPushButton:hover {
            background-color: #2a2a2a;
        }
    )");

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QLabel* title = new QLabel("Choose a map:");
    title->setStyleSheet("font-size: 18px; font-weight: 600; margin-bottom: 10px;");
    mainLayout->addWidget(title, 0, Qt::AlignHCenter);

    QHBoxLayout* buttonsLayout = new QHBoxLayout();

    QPushButton* dustBtn = new QPushButton("Dust");
    QPushButton* aztecBtn = new QPushButton("Aztec Village");
    QPushButton* trainingBtn = new QPushButton("Training Zone");

    connect(dustBtn, &QPushButton::clicked, this, &MapSelectionDialog::selectDust);
    connect(aztecBtn, &QPushButton::clicked, this, &MapSelectionDialog::selectAztec);
    connect(trainingBtn, &QPushButton::clicked, this, &MapSelectionDialog::selectTraining);

    buttonsLayout->addWidget(dustBtn);
    buttonsLayout->addWidget(aztecBtn);
    buttonsLayout->addWidget(trainingBtn);

    mainLayout->addLayout(buttonsLayout);
}

void MapSelectionDialog::selectDust() {
    selectedMap = MapConstants::DUST;
    accept();
}

void MapSelectionDialog::selectAztec() {
    selectedMap = MapConstants::AZTEC_VILLAGE;
    accept();
}

void MapSelectionDialog::selectTraining() {
    selectedMap = MapConstants::TRAINING_ZONE;
    accept();
}

uint8_t MapSelectionDialog::getSelectedMap() const {
    return selectedMap;
}
