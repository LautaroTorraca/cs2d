#pragma once

#include <QDialog>

class QLabel;
class QPushButton;

class ConfirmExitDialog : public QDialog {
Q_OBJECT

public:
    explicit ConfirmExitDialog(QWidget* parent = nullptr);
    bool userConfirmed() const;

private:
    bool confirmed = false;

    void applyStyle();
    void setupUI();

private slots:
    void acceptExit();
    void rejectExit();
};
