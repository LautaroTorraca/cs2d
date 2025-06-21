#include "GameNameDialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

GameNameDialog::GameNameDialog(QWidget* parent,
                               const QString& labelText,
                               const QString& confirmText)
        : QDialog(parent), input(nullptr), confirmBtn(nullptr) {
    setModal(true);
    resize(400, 180);
    setWindowTitle("Game Name");

    setupStyle();
    setupUI(labelText, confirmText);
}

void GameNameDialog::setupStyle() {
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
}

void GameNameDialog::setupUI(const QString& labelText, const QString& confirmText) {
    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* label = new QLabel(labelText);
    layout->addWidget(label);

    input = new QLineEdit(this);
    input->setMaxLength(30);

    QRegularExpression regex("^[\\w]*$");
    QRegularExpressionValidator* validator = new QRegularExpressionValidator(regex, this);
    input->setValidator(validator);

    layout->addWidget(input);

    confirmBtn = new QPushButton(confirmText);
    confirmBtn->setEnabled(false);
    layout->addWidget(confirmBtn, 0, Qt::AlignRight);

    connect(confirmBtn, &QPushButton::clicked, this, &QDialog::accept);
    connect(input, &QLineEdit::textChanged, this, &GameNameDialog::onTextChanged);
}

QString GameNameDialog::getGameName() const {
    QString clean = input->text().trimmed();
    clean.remove('\n');
    clean.remove('\r');
    clean.remove('\t');
    clean.remove(' ');
    return clean;
}

void GameNameDialog::onTextChanged(const QString& text) {
    QString trimmed = text.trimmed();
    QRegularExpression regex("^[\\w]{1,30}$");
    confirmBtn->setEnabled(regex.match(trimmed).hasMatch() && !trimmed.isEmpty());
}