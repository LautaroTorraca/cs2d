#ifndef CREATE_GAME_DIALOG_H
#define CREATE_GAME_DIALOG_H

#include <QDialog>
#include "login/GameDTO.h"

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

#endif // CREATE_GAME_DIALOG_H
