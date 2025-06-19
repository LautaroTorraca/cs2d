#include "GameMenuButton.h"

GameMenuButton::GameMenuButton(const QString& label, QWidget* parent)
        : QPushButton(label, parent) {
    setFixedSize(220, 55);
    setCursor(Qt::PointingHandCursor);
    applyStyle();
}

void GameMenuButton::applyStyle() {
    QString style = R"(
        QPushButton {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                stop:0 rgba(60, 70, 90, 0.9),
                stop:0.5 rgba(45, 55, 75, 0.9),
                stop:1 rgba(35, 45, 65, 0.9));
            color: white;
            border: 2px solid rgba(100, 120, 150, 0.6);
            border-radius: 10px;
            font-size: 16px;
            font-weight: bold;
            text-align: center;
        }
        QPushButton:hover {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                stop:0 rgba(80, 90, 110, 0.95),
                stop:0.5 rgba(65, 75, 95, 0.95),
                stop:1 rgba(55, 65, 85, 0.95));
            border: 2px solid rgba(120, 150, 200, 0.8);
        }
        QPushButton:pressed {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                stop:0 rgba(40, 50, 70, 0.95),
                stop:0.5 rgba(50, 60, 80, 0.95),
                stop:1 rgba(60, 70, 90, 0.95));
            border: 2px solid rgba(80, 100, 130, 0.9);
        }
    )";
    setStyleSheet(style);
}
