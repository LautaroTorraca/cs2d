#pragma once

#include <QDialog>
#include "client/Login/GameDTO.h"

class QSpinBox;
class QPushButton;

class CreateGameDialog : public QDialog {
    Q_OBJECT

private slots:
    void handleConfirm();

private:
    QSpinBox* playerSpinBox;
    QSpinBox* roundsSpinBox;
    QPushButton* confirmButton;

    GameDTO config;

    void setupUI();
    bool isValidRound(int rounds) const;

public:
    explicit CreateGameDialog(QWidget* parent = nullptr);
    GameDTO getGameConfig() const;
};

