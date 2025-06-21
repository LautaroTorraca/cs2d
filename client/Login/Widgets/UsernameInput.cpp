#include "UsernameInput.h"

UsernameInput::UsernameInput(QWidget* parent)
        : QLineEdit(parent) {
    setPlaceholderText("Enter your name");
    setFixedWidth(220);
    setStyleSheet(R"(
        QLineEdit {
            background-color: rgba(255, 255, 255, 0.1);
            color: white;
            font-size: 16px;
            font-weight: bold;
            padding: 12px;
            border: 2px solid rgba(255, 255, 255, 0.2);
            border-radius: 8px;
        }
        QLineEdit:focus {
            border: 2px solid rgba(100, 150, 255, 0.8);
            background-color: rgba(255, 255, 255, 0.15);
        }
        QLineEdit::placeholder {
            color: rgba(255, 255, 255, 0.6);
        }
    )");
}
