#include "ConfirmExitDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

ConfirmExitDialog::ConfirmExitDialog(QWidget* parent)
        : QDialog(parent), confirmed(false) {
    setModal(true);
    setWindowTitle("Confirm Exit");
    resize(300, 150);
    applyStyle();
    setupUI();
}

void ConfirmExitDialog::applyStyle() {
    setStyleSheet(R"(
        QWidget {
            background-color: #1f1f1f;
            color: #ffffff;
            font-family: 'Segoe UI', sans-serif;
        }
        QLabel {
            font-size: 16px;
            padding: 10px;
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

void ConfirmExitDialog::setupUI() {
    auto* layout = new QVBoxLayout(this);
    auto* label = new QLabel("Are you sure you want to exit?");
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);

    auto* buttonLayout = new QHBoxLayout();
    auto* yesBtn = new QPushButton("Yes");
    auto* noBtn = new QPushButton("No");

    buttonLayout->addStretch();
    buttonLayout->addWidget(yesBtn);
    buttonLayout->addWidget(noBtn);
    buttonLayout->addStretch();

    layout->addLayout(buttonLayout);

    connect(yesBtn, &QPushButton::clicked, this, &ConfirmExitDialog::acceptExit);
    connect(noBtn, &QPushButton::clicked, this, &ConfirmExitDialog::rejectExit);
}

void ConfirmExitDialog::acceptExit() {
    confirmed = true;
    accept();
}

void ConfirmExitDialog::rejectExit() {
    confirmed = false;
    reject();
}

bool ConfirmExitDialog::userConfirmed() const {
    return confirmed;
}
