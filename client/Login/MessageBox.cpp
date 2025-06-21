#include "MessageBox.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

MessageBox::MessageBox(QWidget* parent)
        : QDialog(parent) {
    setModal(true);
    setFixedSize(400, 200);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

void MessageBox::showMessage(const QString& title, const QString& message, MessageType type) {
    setWindowTitle(title);
    setStyleSheet(QString(R"(
        QDialog {
            background-color: #1e1e1e;
            border: 2px solid %1;
            border-radius: 10px;
        }
        QLabel {
            color: white;
            font-size: 16px;
        }
        QPushButton {
            background-color: %1;
            color: white;
            border: none;
            border-radius: 8px;
            font-weight: bold;
            padding: 8px 20px;
            font-size: 15px;
        }
        QPushButton:hover {
            background-color: #3a8fd8;
        }
    )").arg(getColorForType(type)));

    auto* layout = new QVBoxLayout(this);

    auto* iconLabel = new QLabel(getIconForType(type) + " " + title);
    iconLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: white;");
    layout->addWidget(iconLabel);

    auto* msgLabel = new QLabel(message);
    msgLabel->setWordWrap(true);
    layout->addWidget(msgLabel);

    auto* button = new QPushButton("OK");
    connect(button, &QPushButton::clicked, this, &QDialog::accept);

    layout->addStretch();
    layout->addWidget(button, 0, Qt::AlignCenter);

    exec();
}

QString MessageBox::getIconForType(MessageType type) const {
    switch (type) {
        case MessageType::Info: return "ℹ️";
        case MessageType::Warning: return "⚠️";
        case MessageType::Error: return "❌";
        case MessageType::Success: return "✅";
    }
    return "🔔";
}

QString MessageBox::getColorForType(MessageType type) const {
    switch (type) {
        case MessageType::Info: return "#007acc";
        case MessageType::Warning: return "#ffcc00";
        case MessageType::Error: return "#e74c3c";
        case MessageType::Success: return "#28a745";
    }
    return "#666";
}
