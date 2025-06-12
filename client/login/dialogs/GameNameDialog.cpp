#include "GameNameDialog.h"
#include <QVBoxLayout>
#include <QLabel>

GameNameDialog::GameNameDialog(QWidget* parent)
        : QDialog(parent) {
    setWindowTitle("Enter Game Name");
    resize(400, 180);
    setModal(true);

    setStyleSheet(R"(
        QWidget {
            background-color: #1e1e1e;
            color: #f0f0f0;
            font-family: 'Segoe UI', sans-serif;
            font-size: 16px;
        }

        QLineEdit {
            background-color: #2a2a2a;
            color: white;
            border: 2px solid #444;
            border-radius: 8px;
            padding: 6px;
            margin-top: 10px;
        }

        QPushButton {
            background-color: #007acc;
            color: white;
            border: none;
            border-radius: 10px;
            font-weight: bold;
            padding: 8px;
            margin-top: 20px;
        }

        QPushButton:hover {
            background-color: #0095ff;
        }

        QPushButton:pressed {
            background-color: #005f99;
        }
    )");

    auto* layout = new QVBoxLayout(this);

    auto* label = new QLabel("Please enter the name of the game you want to join:");
    layout->addWidget(label);

    input = new QLineEdit(this);
    layout->addWidget(input);

    auto* confirmBtn = new QPushButton("Join");
    layout->addWidget(confirmBtn, 0, Qt::AlignRight);

    connect(confirmBtn, &QPushButton::clicked, this, &QDialog::accept);
}

QString GameNameDialog::getGameName() const {
    return input->text().trimmed();
}
