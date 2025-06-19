#pragma once

#include <QDialog>
#include <QString>

enum class MessageType {
    Info,
    Warning,
    Error,
    Success
};

class MessageBox : public QDialog {
Q_OBJECT

public:
    explicit MessageBox(QWidget* parent = nullptr);

    void showMessage(const QString& title, const QString& message, MessageType type = MessageType::Info);

private:
    QString getIconForType(MessageType type) const;
    QString getColorForType(MessageType type) const;
};
